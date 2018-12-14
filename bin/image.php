<?php

$pch = "";
$pauth = "";
$useProxy = 0;
if (file_exists($f = __DIR__."/../proxy.json")) {
	$f = json_decode(file_get_contents($f), true);
	if (isset($f["ch"], $f["username"], $f["password"])) {
		$pch = $f["ch"];
		$useProxy = 1;
		$pauth = "{$f["username"]}:{$f["password"]}";
	}
}

$a = google_image("es teh segar", 3, $useProxy, $pch, $pauth);
var_dump($a);
