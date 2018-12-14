<?php

header("Content-Type: application/json");

if (!isset($_GET["q"])) {

	if (!is_string($_GET["q"])) {
		print json_encode(
			[
				"error" => "\"q\" parameter must be a string"
			]
		);
		exit;
	}

	print json_encode(
		[
			"error" => "\"q\" parameter required!"
		]
	);
	exit;

}

$page = 0;

if (isset($_GET["page"])) {

	if (!is_string($_GET["page"])) {
		print json_encode(
			[
				"error" => "\"page\" parameter must be a string that representate an integer"
			]
		);
		exit;
	}

	if (!is_numeric($_GET["page"])) {
		print json_encode(
			[
				"error" => "\"page\" parameter must be numeric"
			]
		);
		exit;
	}

	$page = (int) $_GET["page"];
}

if ($page < 0) {
	print json_encode(
		[
			"error" => "\"page\" parameter must be greater than -1"
		]
	);
	exit;
}

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

print json_encode(google_image(
	$_GET["q"],
	$page,
	$useProxy,
	$pch,
	$pauth
), JSON_PRETTY_PRINT | JSON_UNESCAPED_SLASHES);
