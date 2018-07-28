from telnet_test import *

class TelnetUptimeCommandTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".uptime")
        result = self.connection.expect([r"no access to run .uptime"])
        return result

class TelnetHelpUptimeCommandTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".help .uptime")
        result = self.connection.expect([r".help: shows how long applications works"])
        return result

class TelnetHelpLoginCommandTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".help .login")
        result = self.connection.expect([r".help: login to system, usage: .login user password"])
        return result

class TelnetHelpCommandSelfTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".help .help")
        result = self.connection.expect([r".help: shows help info about command, i.e. .help <command>"])
        return result

class TelnetHelpCommandNoArgTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".help")
        result = self.connection.expect([r".help: shows help info about command, i.e. .help <command>"])
        return result

class TelnetHelpCommandTooManyArgsTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".help one two")
        result = self.connection.expect([r".help: wrong argument number"])
        return result

class TelnetUnknownCommandTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".unknown")
        result = self.connection.expect([r".unknown: command does not exist!"])
        return result

class TelnetUnknownCommandWithArgTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".unknown arg")
        result = self.connection.expect([r".unknown: command does not exist!"])
        return result

class TelnetLoginNoArgTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".login")
        result = self.connection.expect([r".login: error during command execution"])
        return result

class TelnetLoginTooLessArgTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".login dummy")
        result = self.connection.expect([r".login: error during command execution"])
        return result

class TelnetLoginTooManyArgTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".login dummy dummy dummy")
        result = self.connection.expect([r".login: error during command execution"])
        return result

class TelnetLoginWrongUserTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".login dummy dummy")
        result = self.connection.expect([r".login: access danied"])
        return result

class TelnetLoginWrongPasswordTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".login slaugh dummy")
        result = self.connection.expect([r".login: access danied"])
        return result

class TelnetLoginAccessGrantedTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".login slaugh seb666")
        result = self.connection.expect([r".login: access granted"])
        return result

class TelnetUptimeCommandAfterLoginTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".login slaugh seb666")
        result = self.connection.expect([r".login: access granted"])
        self.connection.send(".uptime")
        result = self.connection.expect([r".uptime: [0-9]+ hours, [0-9]+ minutes, [0-9]+ seconds, [0-9]+ milliseconds"])
        return result

class TelnetLsTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".ls")
        result = self.connection.expect([r".ls: .help .login .ls .uptime"])
        return result