import sys
from junit_xml import TestSuite, TestCase
from testing.telnet_test import *

class TestRunner(object):
    def __init__(self):
        self.results = {}

    def runTest(self, test):
        name = test.getName()
            
        if test.setup() is False:
            print name + " setup FAILED"
            return False
        
        print name + " setup PASSED"

        if test.run() is False:
            print name + " FAILED"
        else:
            print name + " PASSED"

        if test.teardown() is False:
            print name + " teardown FAILED"
            return False

        print name + " teardwond PASSED"
        return True

    def run(self, tests):
        result = True
        for test in tests:
            self.results[test.getName()] = self.runTest(test)
            if self.results[test.getName()] is False:
                result = False

        return result

    def getResults(self):
        return self.results


tests = [ TelnetConnectionTest(), TelnetUptimeCommandTest() ]

runner = TestRunner()
runner.run(tests)
results = runner.getResults()

test_cases = []
for key in results:
    tc = TestCase(key, 'hub.linux.bot', 0, '', '')
    
    if results[key] is False:
        tc.add_failure_info('test failed')    

    test_cases.append(tc)

suite = TestSuite("hub test suite", test_cases)

with open('functional_tests.xml', 'w') as result_file:
    TestSuite.to_file(result_file, [suite], prettyprint=False)

exit(0)

