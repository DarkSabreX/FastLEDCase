'use strict';

angular.module( 'wqLed' )

  .controller( 'SideNavController', ['$timeout','$mdSidenav','$log','comList','sockMsg', function ( $timeout, $mdSidenav, $log, comList, sockMsg )
	{
		var snav = this;
		var test = 'arrow_back';
		snav.comList = comList;
		
		snav.sockMsg = sockMsg;

		snav.leftNavIcon = 'settings';
		snav.rightNavIcon = 'menu';
	
		snav.clickLeftNavIconMorph = function ()
		{
			if ( snav.leftNavIcon === 'settings' )
			{
				snav.leftNavIcon = 'arrow_back';
			}
			else
			{
				snav.leftNavIcon = 'settings';
			}
		};
	
		snav.clickRightNavIconMorph = function ()
		{
			if ( snav.rightNavIcon === 'menu' )
			{
				snav.rightNavIcon = 'arrow_forward';
			}
			else
			{
				snav.rightNavIcon = 'menu';
			}
		};
	
		snav.toggleLeft = buildDelayedToggler( 'left' );
		snav.toggleRight = buildDelayedToggler( 'right' );
	
		/**
		 * Supplies a function that will continue to operate until the
		 * time is up.
		 */
		function debounce( func, wait, context )
		{
			var timer;
			return function debounced()
			{
				var context = this,
					args = Array.prototype.slice.call( arguments );
				$timeout.cancel( timer );
				timer = $timeout( function ()
				{
					timer = undefined;
					func.apply( context, args );
				}, wait || 10 );
			};
		}
		/**
		 * Build handler to open/close a SideNav; when animation finishes
		 * report completion in console
		 */
		function buildDelayedToggler( navID )
		{
		
			return debounce( function ()
			{
				if ( navID === 'left' )
				{
					if ( snav.leftNavIcon === 'settings' )
					{
						snav.leftNavIcon = 'arrow_back';
					}
					else
					{
						snav.leftNavIcon = 'settings';
					}
				}
				if ( navID === 'right' )
				{
					if ( snav.rightNavIcon === 'menu' )
					{
						snav.rightNavIcon = 'arrow_forward';
					}
					else
					{
						snav.rightNavIcon = 'menu';
					}
				}
				// Component lookup should always be available since we are not using `ng-if`
				$mdSidenav( navID )
			    .toggle( )
			    .then( function ()
				{
					$log.debug( "toggle " + navID + " is done" );
				} );
			}, 200 );
		}
	} ]);