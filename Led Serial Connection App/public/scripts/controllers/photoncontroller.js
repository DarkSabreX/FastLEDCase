'use strict';

angular.module( 'wqLed' )

.controller( 'PhotonController', ['$scope','$http', '$filter', 'sockMsg','modeFactory', function ($scope, $http, $filter, sockMsg, modeFactory)
	{
		var photon = this;
		photon.modeFactory = modeFactory;

		$http.get( '/scripts/objects/modegroups.json' ).success( function ( data )
		{
			photon.modeGroupArray = data;
			angular.fromJson( photon.modeGroupArray );
			console.log( photon.modeGroupArray );
			console.log( data );
		} );

		$http.get( '/scripts/objects/modes.json' ).success( function ( data )
		{
			photon.modeList = data;
			angular.fromJson( photon.modeList );
			console.log( photon.modeList );
			console.log( data );
		} );
		
		photon.bufferData = sockMsg.getBufferArray();
		photon.serialBuffer = sockMsg.getConsoleBuffer();
		photon.currentLedMode = '';

		photon.modeGroupArray = modeFactory.getModeGroupArray();
		photon.modeList = modeFactory.getModeList();
		photon.currentMode = '';
		photon.currentHue = modeFactory.cHue();

	}] );