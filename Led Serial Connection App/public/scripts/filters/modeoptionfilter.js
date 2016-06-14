'use strict';

angular.module( 'wqLed' )

.filter( 'modefilter', 'modeList', function ( modeList )
	{
	
		return function (input)
		{
		var mf = this;
	mf.modeList = modeList;
		var out = [];
		angular.forEach( input, function ( mode )
		{
			if ( mode.mode === mf.modeList.selectedModeId )
			{
				out.push( mode.control );
			}
		} );
		return out; 
		}	
	} );