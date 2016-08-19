var Clay = require('pebble-clay');
var clayConfig = require('./config');
var customClay = require('./toggle.js');
var clay = new Clay(clayConfig, customClay);

//Listen for when the watchface is opened
Pebble.addEventListener('ready', 
	function(e)
	{
		console.log("PebbleKit JS ready!");
	}
);