class TestRunner(object):
    def __init__(self):
        self.results = {}

    def runTest(self, test):
        name = test.getName()
        testResult = True

        if test.setup() is False:
            print name + " setup FAILED"
            return False
        
        print name + " setup PASSED"

        if test.run() is False:
            print name + " FAILED"
            testResult = False
        else:
            print name + " PASSED"

        if test.teardown() is False:
            print name + " teardown FAILED"
            return False

        print name + " teardwond PASSED"
        return testResult

    def run(self, tests):
        result = True
        for test in tests:
            self.results[test.getName()] = self.runTest(test)
            if self.results[test.getName()] is False:
                result = False

        return result

    def getResults(self):
        return self.results