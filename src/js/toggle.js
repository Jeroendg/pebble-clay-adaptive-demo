module.exports = function(minified)
{
	var clayConfig = this;
	var _ = minified._;
	var $ = minified.$;
	var HTML = minified.HTML;
	
	function toggleDate()
	{
		if (this.get() == 1)
		{
			clayConfig.getItemByMessageKey('date_format').show();
		}
		else
		{
			clayConfig.getItemByMessageKey('date_format').hide();
		}
	}
	
	clayConfig.on(clayConfig.EVENTS.AFTER_BUILD, function()
	{
		var dateShow = clayConfig.getItemByMessageKey('date_show');
		toggleDate.call(dateShow);
		dateShow.on('change', toggleDate);
	});
};