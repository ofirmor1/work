typedef struct Server Server;

typedef enum SERVER_ERRORS {
	SERVER_SUCCESS = 0,
	SERVER_NOT_INITIALIZED,
	SERVER_NEWCLIENT_ILLEGAL,
	SERVER_OVERFLOW,
	SERVER_FATAL_ERROR,
	SENDING_ERROR,
	RECIEVE_ERROR
	}
 SERVER_ERRORS;


typedef void (*Got_msg)(Server *_myServer,void *msg, int clientID, void* _context1,void* _context2);
typedef SERVER_ERRORS (*Check_new_client)(int clientID);
typedef void* (*close_client)(int clientID);
typedef void (*fail)(Server *_myServer, int error);

typedef struct servParams{
	Got_msg		 GotMessage;
	Check_new_client checkClient;
	close_client 	 closeClient;
	fail 	 	 failMessage;
	int 		 MaxClient;
}servParams;


Server* createServerNet(struct servParams *_parameters, void *_context1, void *_context2);
SERVER_ERRORS RunServer(Server *_myServer);

SERVER_ERRORS sendMessage(Server *_myServer, int clientId, void* info, int dataLen);

void destroyServer(Server **_myServer);

void StopServer(Server *_myServer);


