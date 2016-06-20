'use strict';

angular.module( 'wqLed')

  .controller( 'PortSelectController', ['$mdDialog','$mdMedia', 'comList','sockMsg', function ( $mdDialog, $mdMedia, comList, sockMsg)
	{
		var pc = this;
		pc.sockMsg = sockMsg;
		pc.comList = comList;

		
		pc.status = '  ';
		pc.customFullscreen = $mdMedia( 'xs' ) || $mdMedia( 'sm' );
		
		pc.showComSelect = function ( ev )
		{
			$mdDialog.show( {
				controller: DialogController,
				controllerAs: 'dc',
				templateUrl: 'views/comsel.tmpl.html',
				parent: angular.element( document.body ),
				locals: {
					sockMsg: sockMsg,
					comList: comList
				},
				preserveScope: true,
				targetEvent: ev,
				clickOutsideToClose: false
			} );
		};

		function DialogController( $mdDialog, sockMsg, comList )
		{
			var dc = this;
			dc.sockMsg = sockMsg;
			dc.comList = comList;
			dc.hide = function ()
			{
				$mdDialog.hide( );
			};

			dc.finalPortSet = function ()
			{
				dc.sockMsg.selPort( );
				$mdDialog.hide( );
			};
		}
	}] );