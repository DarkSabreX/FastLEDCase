'use strict';

angular.module( 'wqLed' )

  .factory( 'comList', function ()
{
	var comList = {};
	comList.isPortSet = false;
	comList.comNames = [];
	comList.portSelected = "";
	
	return {
		updateComList: function ( list )
		{
			comList.comNames = list;
		},
		showComList: function ()
		{
			return comList.comNames;
		},
		setComPort: function ( port )
		{
			comList.portSelected = port;
			comList.isPortSet = true;
		},
		showComPort: function ()
		{
			return comList.portSelected;
		},
		checkPortSet: function ()
		{
			return comList.isPortSet;
		},
	};
	return comList;

} );