'use strict';

angular.module( 'wqLed' )

.config( function ($stateProvider)
{
	$stateProvider
	.state( 'photon', {
		url: "",
		controller: "SideNavController as snav",
		templateUrl: "/views/partials/maincontainer.html",
		views: {
			'leftNav': {
				controller: "SideNavController as snav",
				templateUrl: "/views/partials/leftnav.html"
			}, 
			'rightNav': {
				controller: "SideNavController as snav",
				templateUrl: "/views/partials/rightnav.html"
			}, 
			'maincontent': {}, 
		
		}
	})
	/*.state( 'photon.leftNav', {
		url: "",
		controller: "SideNavController as snav",
		templateUrl: "/views/partials/leftnav.html"
	} )
	.state( 'photon.rightNav', {
		url: "",
		controller: "SideNavController as snav",
		templateUrl: "/views/partials/rightnav.html"
	} )
	.state( 'photon.maincontent', {
	} )*/
} );