<?php
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$ 
 * 
 * @file kdiff.php
 * @author zhongligang <ZhongLigang@gmail.com>
 * @date 2012-01-29 11:20:31
 */

define("DEBUG", TRUE);
if (defined("DEBUG")) {
    $fin = fopen("input03.txt", "r");
} else {
    $fin = fopen("php://stdin", "r");
}

fscanf($fin, "%d %d\n", $numbers, $difference);
$set = trim(fgets($fin));
$set = explode(" ", $set);
array_walk($set, "convert_to_int");
sort($set);

$len = count($set);
$start = 0;
$end = 1;

$finded = 0;
while ($end < $len) {
    if ($set[$end] - $set[$start] === $difference) {
        $finded++;
        $start++;
        $end++;
    } elseif ($set[$end] - $set[$start] < $difference) {
        $end++;
    } else {
        $start++;
        if ($start === $end) {
            $end++;
        }
    }
}

echo "$finded\n";

function convert_to_int(&$val, $key)
{
    $val = (int) $val;
}
/* vim: set ts=4 sw=4 sts=4 tw=100 et: */
