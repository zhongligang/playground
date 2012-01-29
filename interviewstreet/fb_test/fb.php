<?php
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$ 
 * 
 * @file fb.php
 * @author zhongligang <ZhongLigang@gmail.com>
 * @date 2012-01-28 22:26:48
 */
define("MAX_STEP", 7);
define("DEBUG", TRUE);
if (defined("DEBUG")) {
    $fin = fopen("input01.txt", "r");
    $fout = fopen("php://stdout", "w");
} else {
    $fin = fopen("php://stdin", "r");
    $fout = fopen("php://stdout", "w");
}

$input = trim(fgets($fin));
list($discs, $pegs) = explode(" ", $input);
$input = trim(fgets($fin));
$initial = explode(" ", $input);
$input = trim(fgets($fin));
$final = explode(" ", $input);

$initial_peg_hold = array();
$initial_peg_hold = array_pad($initial_peg_hold, $pegs + 1, array());
foreach ($initial AS $radius=>$peg_num) {
    array_unshift($initial_peg_hold[$peg_num], $radius + 1);
}

$final_peg_hold = array();
$final_peg_hold = array_pad($final_peg_hold, $pegs + 1, array());
foreach ($final AS $radius=>$peg_num) {
    array_unshift($final_peg_hold[$peg_num], $radius + 1);
}

unset($initial_peg_hold[0]);
unset($final_peg_hold[0]);
$queue = array(array($initial_peg_hold, array(), 0));
do_bfs($queue, MAX_STEP);

function do_bfs($queue, $max_step)
{
    global $final_peg_hold;

    while($params = array_shift($queue)) {
        if ($params[2] >= $max_step) {
            return FALSE;
        }
        $initial = $params[0];
        $previous_steps = $params[1];
        $current_step = $params[2];
        foreach ($initial AS $peg_num=>$discs) {
            if (empty($discs)) {
                continue;
            }
            foreach ($initial AS $peg_num2=>$discs2) {
                if ($peg_num2 !== $peg_num && (empty($discs2) || $discs[count($discs) - 1] < $discs2[count($discs2) - 1])) {
                    if (count($previous_steps) > 0 && "$peg_num2 $peg_num" == $previous_steps[count($previous_steps) - 1]) {
                        continue;
                    }
                    $_previous_steps = $previous_steps;
                    $_previous_steps[] =  "$peg_num $peg_num2";
                    $_initial = $initial;
                    array_push($_initial[$peg_num2], array_pop($_initial[$peg_num]));
                    if (status_equal($_initial, $final_peg_hold)) {
                        print_result($_previous_steps);
                        return TRUE;
                    } else {
                        array_push($queue, array($_initial, $_previous_steps, $current_step + 1));
                    }
                }
            }
        }
    }
}

function status_equal($a, $b)
{
    foreach ($a AS $k1=>$v1) {
        foreach ($v1 AS $k=>$v) {
            if (!isset($b[$k1][$k]) || $b[$k1][$k] !== $v) {
                return FALSE;
            }
        }
    }
    
    return TRUE;
}

function print_result($steps)
{
    $output = count($steps) . "\n" . implode("\n", $steps);

    echo $output, "\n";
}

/* vim: set ts=4 sw=4 sts=4 tw=100 et: */
