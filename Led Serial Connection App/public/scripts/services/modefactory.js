'use strict';

angular.module( 'wqLed' )

  .factory( 'modeFactory', function ( $http, $filter )
{
	var modeFactory = {};
	modeFactory.modeGroupArray = [];
	modeFactory.modeList = [];

	modeFactory.modeNow = { mode: "0" };
	
	var curmde = "0";
	modeFactory.cMode = function ( modeSet )
	{
		return arguments.length ? ( curmde = modeSet ) : curmde; 
	};
	var curhue = "0";

	modeFactory.cHue = function ( hueSet )
	{
		return arguments.length ? ( curhue = hueSet ) : curhue;
	};


	return {
		setModeGroupArray: function ( mg )
		{
			modeFactory.modeGroupArray = mg;
		},
		getModeGroupArray: function ()
		{
			return modeFactory.modeGroupArray;
		},
		setModeList: function ( ml )
		{
			modeFactory.modeList = ml;
		},
		getModeList: function (){
			return modeFactory.modeList;
		},
		setCurrentMode: function ( ml )
		{
			modeFactory.modeNow = ml;
		},
		getCurrentMode: function ()
		{
			return modeFactory.modeNow;
		},
		cMode: modeFactory.cMode,
		cHue: modeFactory.cHue,
		
	};
	return modeFactory;
} );