import sys

class Test(object):
    def __init__(self, name):
        self.name = name

    def setup(self):
        return True

    def teardown(self):
        return True

    def run(self):
        print "Starting test: " + self.name
        return True
        