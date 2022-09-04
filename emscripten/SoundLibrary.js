mergeInto(LibraryManager.library, {
	SoundManagerAdd: function (name, filename) {
		name = UTF8ToString(name);
		filename = UTF8ToString(filename);
		//console.log('js add name '+name+' filename '+filename);
		Module.SoundManagerAdd(name, filename);
	},

	SoundManagerPlay: function (name) {
		name = UTF8ToString(name);
		//console.log('js play '+name);
		Module.SoundManagerPlay(name);
	},

	SoundManagerPause: function (name) {
		name = UTF8ToString(name);
		//console.log('js pause '+name);
		Module.SoundManagerPause(name);
	},

	SoundManagerStop: function (name) {
		name = UTF8ToString(name);
		//console.log('js stop '+name);
		Module.SoundManagerStop(name);
	},

	SoundManagerLoop: function (name) {
		name = UTF8ToString(name);
		//console.log('js loop '+name);
		Module.SoundManagerLoop(name);
	},

	SoundManagerSetGain: function (name, gain) {
		name = UTF8ToString(name);
		//console.log('js gain '+name);
		Module.SoundManagerSetGain(name, gain);
	},

});