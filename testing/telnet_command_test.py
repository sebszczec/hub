from telnet_test import *

class TelnetUptimeCommandTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".uptime")
        result = self.connection.expect([r"[0-9]+ hours, [0-9]+ minutes, [0-9]+ seconds, [0-9]+ milliseconds"])
        return result

class TelnetHelpCommandTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".help .uptime")
        result = self.connection.expect([r"Shows how long applications works"])
        return result

class TelnetHelpCommandSelfTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".help .help")
        result = self.connection.expect([r"Shows help info about command, i.e. .help <command>"])
        return result

class TelnetHelpCommandNoArgTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".help")
        result = self.connection.expect([r"Shows help info about command, i.e. .help <command>"])
        return result

class TelnetHelpCommandTooManyArgsTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".help one two")
        result = self.connection.expect([r""])
        return result