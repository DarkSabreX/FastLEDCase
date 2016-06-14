var modeList = {
	groups:
 [	
		{
			group: 'noAnim',
			id: '1',
			title: 'Static Modes',
			modes: [

				{
					mode: '0',
					name: 'Mode 0',
					code: 'm0',
					desc: 'All Off',
					icon: {
						name: 'brightness_high',
						fill: 'black'
					}
				},
				{
					mode: '1',
					name: 'Mode 1',
					code: 'm1',
					desc: 'All On - White',
					icon: {
						name: 'brightness_high',
						fill: 'gray'
					}
				},
				{
					mode: '2',
					name: 'Mode 2',
					code: 'm2',
					desc: 'All On - Selectable',
					icon: {
						name: 'brightness_high',
						fill: 'gray'
					},
					controls: [{
							name: 'color',
							isAvail: 'yes'
						},
						{
							name: 'speed',
							isAvail: 'yes'
						},
						{
							name: 'direction',
							isAvail: 'no'
						}
					]
				}]
		},
		{
			group: 'animFill',
			id: '2',
			title: 'Basic Animated Fills',
			modes: [

				{
					mode: '6',
					name: 'Mode 6',
					code: 'm6',
					desc: 'All wacky right now',
					icon: {
						name: 'brightness_high',
						fill: 'black'
					}
				},
				{
					mode: '7',
					name: 'Mode 7',
					code: 'm7',
					desc: 'test content',
					icon: {
						name: 'brightness_high',
						fill: 'black'
					}
				}]
		}
	]
};