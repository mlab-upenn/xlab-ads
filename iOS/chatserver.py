from twisted.internet.protocol import Protocol, Factory
from twisted.internet import reactor

class IphoneChat(Protocol):
	def connectionMade(self):
		#self.transport.write("""connected""")
		self.factory.clients.append(self)
		print "clients are ", self.factory.clients
	
	def connectionLost(self, reason):
	    self.factory.clients.remove(self)
	    print "connection lost"
	
	def dataReceived(self, data):
	        print "data is ", data
		a = data.split(':')
		if len(a) > 1:
			command = a[0]
			content = a[1]		
			msg = ""
			if command == "iam":
				msg = "hello world"
			elif command == "video":
				msg = "video:"+content				
			elif command == "msg":
			    msg = "image:"+content
			print msg				
			for c in self.factory.clients:
				c.message(msg)
				
	def message(self, message):
		self.transport.write(message + '\n')


factory = Factory()
factory.protocol = IphoneChat
factory.clients = []

reactor.listenTCP(1234, factory)
print "Iphone Chat server started"
reactor.run()

