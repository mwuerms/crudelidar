/**
 * Martin Egli
 * 2025-11-24
 * parts for crude lidar
 */

module nema17_m3_cut(h1 = 10, loc_res = 32) {
    for(n = [0:1:3])
    translate([22*cos(45+n*90), 22*sin(45+n*90), 0])
    cylinder(d = 3, h = h1, $fn = loc_res);
}

module nema17_top_cut(h1 = 10, loc_res = 32) {
    translate([0, 0, 0])
    nema17_m3_cut(h1 = h1, loc_res = loc_res);
    translate([0, 0, 0])
    cylinder(d = 22.5, h = h1, $fn = loc_res);
}

module nema17(loc_res = 32) {
    difference() {
        union() {
            // bottom
            color("LightGray")
            translate([0, 0, 0])
            hull() {
                translate([-42/2, -34/2, 0])
                cube([42, 34, 11]);
                translate([-34/2, -42/2, 0])
                cube([34, 42, 11]);
            }
            // connector
            color("LightGray")
            translate([-17/2, -42/2-6, 0])
            cube([17, 6+1, 11]);
            // middle
            color("Black")
            translate([0, 0, 11])
            hull() {
                translate([-42/2, -34/2, 0])
                cube([42, 34, 11]);
                translate([-34/2, -42/2, 0])
                cube([34, 42, 11]);
            }
            // top
            color("LightGray")
            translate([0, 0, 22])
            hull() {
                translate([-42/2, -34/2, 0])
                cube([42, 34, 11]);
                translate([-34/2, -42/2, 0])
                cube([34, 42, 11]);
            }
            // 22 mm on top
            color("LightGray")
            translate([0, 0, 33])
            cylinder(d = 22, h = 2, $fn = loc_res);
            // 5mm spindle
            color("LightGray")
            translate([0, 0, 1])
            cylinder(d = 5, h = 56, $fn = loc_res);
        }
        translate([0, 0, 25])
        nema17_m3_cut();
    }
}
//nema17();

module pcb_vl53l1x_satel(loc_res = 32) {
    // pcb
    color("Green")
    translate([0, 0, 0])
    cube([26.5, 14, 1.5]);
    // sensor
    color("DarkGray")
    translate([19.8, 5.1, 1.5])
    cube([2.2, 3.8, 1.5]);
    // voltage translator
    color("DarkGray")
    translate([6.9, 5.3, -1.5])
    cube([7.1, 4.6, 1.5]);
}
//pcb_vl53l1x_satel();

module pcb_vl53l1x_satel_cut_bottom(loc_res = 32) {
    // space pcb
    translate([-0.25, -0.25, 0])
    cube([27, 14.5, 3]);
    // space voltage translator
    translate([6.9-0.2, 5.3-0.2, -2])
    cube([7.5, 5.1, 3.1]);
    // space components
    translate([14, -0.2, -2])
    cube([10, 14.5, 3.1]);
}
pcb_vl53l1x_satel_cut_bottom();
