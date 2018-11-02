import time

class FontColor:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

class TestMarker:
    PASSED = FontColor.OKBLUE + "[PASSED]" + FontColor.ENDC
    FAILED = FontColor.FAIL + "[FAILED]" + FontColor.ENDC

class TestRunner(object):
    def __init__(self):
        self.results = {}

    def runTest(self, test, prefix):
        name = prefix + test.getName()
        testResult = True

        if test.setup() is False:
            print TestMarker.FAILED + "[Setup]....." + FontColor.OKGREEN + name  + FontColor.ENDC
            return False
        
        print TestMarker.PASSED +  "[Setup]....." + FontColor.OKGREEN + name  + FontColor.ENDC

        if test.run() is False:
            print TestMarker.FAILED + "[Test]......" + FontColor.OKGREEN + name  + FontColor.ENDC
            testResult = False
        else:
            print TestMarker.PASSED +  "[Test]......" + FontColor.OKGREEN + name  + FontColor.ENDC

        if test.teardown() is False:
            print TestMarker.FAILED + "[Teardown].." + FontColor.OKGREEN + name  + FontColor.ENDC
            return False

        print TestMarker.PASSED + "[Teardown].." + FontColor.OKGREEN + name  + FontColor.ENDC
        return testResult

    def run(self, tests, prefix):
        result = True
        for test in tests:
            name = prefix + test.getName()
            self.results[name] = self.runTest(test, prefix)
            if self.results[name] is False:
                result = False

        return result

    def getResults(self):
        return self.results