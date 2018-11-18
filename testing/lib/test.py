import sys

class Test(object):
    def __init__(self):
        self.name = type(self).__name__
        self.test_with_ssl = True

    def setup(self):
        return True

    def teardown(self):
        return True

    def run(self):
        return True

    def getName(self):
        return self.name

        