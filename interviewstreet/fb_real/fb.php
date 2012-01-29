<?php
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$ 
 * 
 * @file fb.php
 * @author zhongligang <ZhongLigang@gmail.com>
 * @date 2012-01-28 22:26:48
 */
define("DEBUG", TRUE);
if (defined("DEBUG")) {
    $fin = fopen("input01.txt", "r");
} else {
    $fin = fopen("php://stdin", "r");
}

fscanf($fin, "%d\n", $num_testcast);
for ($i = 0; $i < $num_testcast; $i++) {
    fscanf($fin, "%d %d %d\n", $containers, $blackballs, $probability);

    calc_whiteball($containers, $blackballs, $probability);
}

function calc_whiteball($containers, $blackballs, $probability)
{
    $min = max(0, $containers - $blackballs);
    // max probability when user least balls
    $p_min = floor(100 * $min / $containers);

    // just fill all containers
    if ($probability <= $p_min) {
        echo $min, "\n";
        return TRUE;
    // every container should have one white ball
    } elseif ($probability === 100 && $blackballs === 0) {
        echo $containers, "\n";
        return TRUE;
    }

    if ($probability <= floor(100 * ($containers - 1) / $containers)) {
        echo max(0, ceil($probability * $containers / 100)), "\n";
        return TRUE;
    }

    $balls = ceil(100 * $blackballs / ($containers * (100 - $probability)) - $blackballs);
    if ($balls <= 0) {
        $balls = 0;
    }

    echo max(0, $balls + $containers - 1), "\n";
    return TRUE;
}
/* vim: set ts=4 sw=4 sts=4 tw=100 et: */
