'use strict';

angular.module( 'wqLed' )

  .factory('modeList', function ($http)
{
	var modeList = this;
	
	modeList.getModes = function ()
	{
		$http.get( '/scripts/objects/modelist.json' )
		.success( function ( data )
		{
			modeList.modeGroup = data;
		} );
		return modeList.modeGroup;
	};

	return modeList;
} )