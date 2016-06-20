'use strict';

angular.module( 'wqLed' )

  .service( 'modeListService', function ( $http, $filter )
{
	var portBuffer = [];
	var modeArray = {};
	var modeTest = 'test';
	var selectedModeId = 2;
	var selectedMode = {};
	
	
	return {
		getModeArray: function ()
		{
			return modeArray; 
		},
		setModeArray: function ( data ){
			modeArray = data;
		},
		getSelectedMode: function (){
			return selectedMode;
		},

		setSelectedMode: function ( mode )
		{
			selectedMode = mode;
		},
		getSelectedModeId: function ()
		{
			return selectedModeId;
		},
		
		setSelectedModeId: function ( mode )
		{
			selectedModeId = mode;
		},
		getPortBuffer: function (){
			return portBuffer;
		},
		setPortBuffer: function (buff)
		{
			portBuffer = buff; 
		},
		getModeTest: function ()
		{
			return modeTest;
		}
	}
	
	

	
	

} );