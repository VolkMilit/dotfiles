// Version: 2014-09-24

// Obsolete function
function aclara(a) {
	var d = a.split(".");
	var id = d[0].length + "." + (a.length - d[0].length - 1);

	if (id == "45.40") {
		return aclara_f(a);
	}
	return "";
}

function aclara_p(a,p) {
	var d = a.split(".");
	var id = d[0].length + "." + (a.length - d[0].length - 1);

	if ((p == "en_US-vflx8EenD") || (id == "45.40")) {
		return aclara_f(a);
	}
	return "";
}

function aclara_f(a) {
	a=a.split("");
	uq.yt(a,8);
	uq.wg(a,3);
	uq.yt(a,45);
	uq.yt(a,46);
	uq.wg(a,2);
	uq.yt(a,29);
	uq.yt(a,25);
	uq.yt(a,56);
	uq.yt(a,2);
	return a.join("");
}

var uq ={wg:function(a,b){a.splice(0,b)},SM:function(a){a.reverse()},yt:function(a,b){var c=a[0];a[0]=a[b%a.length];a[b]=c} };

// A: NDUuNDA=
// B: ZW5fVVMtdmZseDhFZW5E
// C: MjAxNC0wOS0yNA==
// D: c3RzPTE2MzM0
// E: dXE=
