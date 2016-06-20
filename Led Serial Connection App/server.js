//node module requires for web and websockets server
var express = require( 'express' );
var morgan = require( 'morgan' );
var bodyParser = require( 'body-parser' );
var methodOverride = require( 'method-override' );
var app = express( );

//require socket.io
var io = require( 'socket.io' );
//require serialport
var serialport = require( 'serialport' );
var SerialPort = serialport.SerialPort;

var serverPort = '4567';


app.use( express.static( __dirname + '/public' ) ); 	// set the static files location /public/img will be /img for users
app.use( '/angular', express.static( __dirname + '/node_modules/angular-io/bin' ) );     // set static files location for io js files
app.use( '/io', express.static( __dirname + '/node_modules/socket.io-client' ) );     // set static files location for io js files
app.use( '/angular', express.static( __dirname + '/node_modules/angular-socket-io' ) );     // set static files location for angular socket io js files
app.use( '/angular', express.static( __dirname + '/node_modules/angular' ) );     // set static files location for angular js files
app.use( '/angular', express.static( __dirname + '/node_modules/angular-aria' ) );     // set static files location for angular animate
app.use( '/angular', express.static( __dirname + '/node_modules/angular-animate' ) );     // set static files location for angular animate
app.use( '/angular', express.static( __dirname + '/node_modules/angular-messages' ) );     // set static files location for angular messages
app.use( '/angular', express.static( __dirname + '/node_modules/angular-material' ) );     // set static files location for angular material
app.use( '/angular', express.static( __dirname + '/node_modules/angular-material-icons' ) );     // set static files location for material icons
app.use( '/angular', express.static( __dirname + '/node_modules/svg-morpheus/compile/unminified' ) );
app.use( '/angular', express.static( __dirname + '/node_modules/v-accordion/dist' ) );
app.use( '/angular', express.static( __dirname + '/node_modules/angular-ui-router/release' ) );


app.use( morgan( 'dev' ) ); 					// log every request to the console
app.use( bodyParser( ) ); 						// pull information from html in POST
app.use( methodOverride( ) ); 					// simulate DELETE and PUT






// make a socket server using the express server
var server = require( 'http' ).Server( app );
var socketServer = io( server );


//Start the Express Server
server.listen( serverPort, function ()
{
	console.log( 'Simple static server listening on port '+serverPort );
} );




var sPortList = { sPortList: [] };
var ioPort = '';
//data in from client
var readData = '';

//serialport connection
var lastMode = [];





// list serial ports:
serialport.list( function ( err, ports )
{
	ports.forEach( function ( port )
	{
		sPortList.sPortList.push( { comName: port.comName } );
	} );
} );

// Web Socket Connection
//Creates handler when a connection is opened
socketServer.sockets.on( 'connection', function ( socket )
{
	console.log( "Socket connected" );
	socket.emit( 'connected', sPortList );
	// If a web browser disconnects from Socket.IO then this callback is called.
	socket.on( "disconnect", function ()
	{
		console.log( "disconnected" );
	} );
	
	
	//Event: listPorts Desc: Lists com ports. Will allow for selection of ports
	socket.on( 'listPorts', function ()
	{
		socket.emit( 'portList', sPortList );
		console.log( "Sent comPort List" );
	} );
	
	//Event: setPort 
	socket.on( 'setPort', function ( data )
	{
		console.log( 'Setting ' + data + ' as port' );
		ioPort = data;
		console.log( ioPort );
		socket.emit( 'portSet', 'Ready to connect!' );
	} );
	
	//Event: tConn Desc: Serialport commands here.
	socket.on( 'tConn', function ( data )
	{
		console.log( 'SerialPort Connection established!' );
		var sp = new SerialPort( ioPort, {
			autoOpen: false,
			baudRate: 115200,
			buffersize: 65536,
			parser: serialport.parsers.readline( '\n' )
		}, false );
		
		//serialport functions
		
		
		sp.on( 'open', onPortOpen );
		sp.on( 'data', onData );
		sp.on( 'close', onClose );
		sp.on( 'error', onError );
		
		sp.open( function ( )
		{
			console.log( "reading serial data" + onData );			
		} );
		socket.on( 'mChg', function ( data )
		{
			sp.write( new Buffer( data ) );
		} );
		socket.on( 'hChg', function ( hue )
		{
			sp.write( new Buffer( 'h' + hue ) );
		} );
		
		socket.on( 'eConn', function ()
		{
			sp.close( );
		} );
	} );
	

} );





function onPortOpen()
{
	console.log( "Serial Port on " + ioPort + " open" );
}

function onData( data )
{
	var mode = data;
	if ( lastMode !== mode )
	{
		socketServer.sockets.emit( 'sData', mode );
	}
	lastMode = mode;
	
	//console.log("data dis, data dat " + data);
	
}

function onClose()
{
	lastMode = [];
	console.log( "SerialPort is closed." );
}
function onError(err)
{
	console.log( "Error:" + err.message );

}