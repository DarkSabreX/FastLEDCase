'use strict';

angular.module( 'wqLed' )

  .factory( 'comList', function ()
{
	var comList = [];
	comList.isPortSet = false;

	comList.updateComList = function ( list ){
		comList.comName = list;
	}
	
	comList.showComList = function (){
		return comList.comName;
	}
	
	comList.setComPort = function ( port ){
		comList.portSelected = port;
		comList.isPortSet = true; 
	}

	comList.showComPort = function (){
		return comList.portSelected;
	}
	
	comList.checkPortSet = function (){
		return comList.isPortSet;
	}

	return comList; 
} );