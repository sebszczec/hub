from telnet_test import *

class TelnetUptimeCommandTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".uptime")
        result = self.connection.expect(".uptime: no access to run .uptime\n")
        return result

class TelnetHelpUptimeCommandTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".help .uptime")
        result = self.connection.expect(".help: shows how long applications works\n")
        return result

class TelnetHelpLoginCommandTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".help .login")
        result = self.connection.expect(".help: login to system, usage: .login user password\n")
        return result

class TelnetHelpCommandSelfTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".help .help")
        result = self.connection.expect(".help: shows help info about command, i.e. .help <command>\n")
        return result

class TelnetHelpCommandNoArgTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".help")
        result = self.connection.expect(".help: shows help info about command, i.e. .help <command>\n")
        return result

class TelnetHelpCommandTooManyArgsTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".help one two")
        result = self.connection.expect(".help: wrong argument number\n")
        return result

class TelnetUnknownCommandTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".unknown")
        result = self.connection.expect(".unknown: command does not exist!\n")
        return result

class TelnetUnknownCommandWithArgTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".unknown arg")
        result = self.connection.expect(".unknown: command does not exist!\n")
        return result

class TelnetLoginNoArgTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".login")
        result = self.connection.expect(".login: error during command execution\n")
        return result

class TelnetLoginTooLessArgTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".login dummy")
        result = self.connection.expect(".login: error during command execution\n")
        return result

class TelnetLoginTooManyArgTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".login dummy dummy dummy")
        result = self.connection.expect(".login: error during command execution\n")
        return result

class TelnetLoginWrongUserTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".login dummy dummy")
        result = self.connection.expect(".login: access danied\n")
        return result

class TelnetLoginWrongPasswordTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".login slaugh dummy")
        result = self.connection.expect(".login: access danied\n")
        return result

class TelnetLoginAccessGrantedTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".login slaugh seb666")
        result = self.connection.expect(".login: access granted\n")
        return result

class TelnetUptimeCommandAfterLoginTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".login slaugh seb666")
        result = self.connection.expect(".login: access granted\n")
        self.connection.send(".uptime")
        result = self.connection.expect(".uptime:")
        return result

class TelnetLsTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".ls")
        result = self.connection.expect(".ls: .help .login .logout .ls .uptime\n")
        return result

class TelnetLogoutCommandTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".logout")
        result = self.connection.expect(".logout: no access to run .logout\n")
        return result

class TelnetLogoutCommandAfterLoginTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".login slaugh seb666")
        result = self.connection.expect(".login: access granted\n")
        self.connection.send(".logout")
        result = self.connection.expect(".logout: logout successful\n")
        self.connection.send(".logout")
        result = self.connection.expect(".logout: no access to run .logout\n")
        return result

class TelnetWhoamiCommandTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".whoami")
        result = self.connection.expect(".whoami: no access to run .whoami\n")
        return result

class TelnetWhoamiCommandAfterLoginTest(TelnetTest):
    def run(self):
        Test.run(self)
        self.connection.send(".login slaugh seb666")
        result = self.connection.expect(".login: access granted\n")
        self.connection.send(".whoami")
        result = self.connection.expect(".whoami: slaugh\n")
        self.connection.send(".logout")
        result = self.connection.expect(".logout: logout successful\n")
        self.connection.send(".whoami")
        result = self.connection.expect(".whoami: no access to run .whoami\n")
        return result
