'use strict';

angular.module( 'wqLed')

  .controller( 'PortSelectController', ['$mdDialog','$mdMedia', 'comList','sockMsg', function ( $mdDialog, $mdMedia, comList, sockMsg)
	{
		var pc = this;
		pc.comList = comList;
		pc.sockMsg = sockMsg;
		
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
					sMsg: pc.sockMsg,
					cList: pc.comList
				},
				preserveScope: true,
				targetEvent: ev,
				clickOutsideToClose: false
			} );
		};

		function DialogController( $mdDialog, sMsg, cList )
		{
			var dc = this;
			dc.socketMsg = sMsg;
			dc.comList = cList;
			dc.hide = function ()
			{
				$mdDialog.hide( );
			};

			dc.finalPortSet = function ()
			{
				dc.socketMsg.selPort( );
				$mdDialog.hide( );
			};
		}
	}] );