var randFromZeroToMax = (max) => {
	return Math.floor(Math.random() * max);
};

var randFromMinToMax = (min, max) => {
	return Math.floor(Math.random() * (max - min)) + min;
};

var randByPoisson = (lambda) => {
	let pn = 0.15;
	let n = Math.floor(lambda / pn);
	let counter = 0;

	for (let i = 0; i < n; ++i) {
		if (Math.random() < pn) ++counter;
	}

	return counter;
}