'use strict';

angular.module( 'wqLed' )

  .factory( 'modeList',['sockMsg', function ( $http, $filter, sockMsg )
{
	var modeList = this;
	modeList.selectedModeId = '0';
	modeList.selectedMode = [];
	
	modeList.setMode = function ( mode )
	{
		modeList.selectedModeId = mode;

	}
	
	modeList.getMode = function ()
	{
		return modeList.selectedModeId;
	}
	
	return modeList;
} ]);