import sys
from junit_xml import TestSuite, TestCase
from testing.telnet_test import *
from testing.test_runner import *

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

