module.exports = 
[
	{
		"type": "heading",
		"id": "main-heading",
		"defaultValue": "clay-demo",
		"size": 1
	},
	{
		"type": "section",
		"items": [
		{
			"type": "heading",
			"defaultValue": "Colors"
		},
		{
			"type": "color",
			"messageKey": "back",
			"defaultValue": "FFFFFF",
			"label": "Background Color",
			"sunlight": true,
			"allowGray": true
		},
		{
			"type": "color",
			"messageKey": "text",
			"defaultValue": "000000",
			"label": "Text Color",
			"sunlight": false,
			"allowGray": false
		}]
	},
	{
		"type": "section",
		"items": [
		{
			"type": "heading",
			"defaultValue": "Date"
		},
		{
			"type": "toggle",
			"messageKey": "date_show",
			"label": "Show Date",
			"defaultValue": true
		},
		{
			"type": "select",
			"messageKey": "date_format",
			"defaultValue": "%Y-%m-%d",
			"label": "Date Format",
			"options": [
			{
				"label": "2016-12-31",
				"value": "%Y-%m-%d"
			},
			{
				"label": "31-12-2016",
				"value": "%d-%m-%Y"
			},
			{
				"label": "12-31-2016",
				"value": "%m-%d-%Y"
			}]
		}]
	},
	{
		"type": "section",
		"id": "submit",
		"items": [
		{
			"type": "submit",
			"defaultValue": "Save"
		}]
	}
];