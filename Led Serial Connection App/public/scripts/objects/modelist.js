﻿var modeListArr = {
	groups:
 [	
		{
			group: 'noAnim',
			id: '1',
			title: 'Static Modes',
			modes: [

				{
					id: '0',
					name: 'Mode 0',
					code: 'm0',
					desc: 'All Off',
					icon: {
						name: 'brightness_high',
						fill: 'black'
					}
				},
				{
					id: '1',
					name: 'Mode 1',
					code: 'm1',
					desc: 'All On - White',
					icon: {
						name: 'brightness_high',
						fill: 'gray'
					}
				},
				{
					id: '2',
					name: 'Mode 2',
					code: 'm2',
					desc: 'All On - Static Rainbow',
					icon: {
						name: 'brightness_high',
						fill: 'gray'
					},
					controls: [{
							name: 'color',
							isAvail: 'yes',
							value: 'blue'
						},
						{
							name: 'speed',
							isAvail: 'yes',
							value: '1',
						},
						{
							name: 'direction',
							isAvail: 'no',
							value: 'f'
						}
					]
				},
				{
					id: '3',
					name: 'Mode 3',
					code: 'm3;h145',
					desc: 'All On - Selectable Color',
					icon: {
						name: 'brightness_high',
						fill: 'gray'
					},
					controls: [{
							name: 'color',
							isAvail: 'yes',
							value: 'blue'
						},
						{
							name: 'speed',
							isAvail: 'yes',
							value: '1',
						},
						{
							name: 'direction',
							isAvail: 'no',
							value: 'f'
						}
					]
				}
			]
		},
		{
			group: 'animFill',
			id: '2',
			title: 'Basic Animated Fills',
			modes: [

				{
					id: '6',
					name: 'Mode 6',
					code: 'm6',
					desc: 'All wacky right now',
					icon: {
						name: 'brightness_high',
						fill: 'black'
					}
				},
				{
					id: '7',
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