/**
 * Martin Egli
 * 2025-11-24
 * parts for crude lidar
 */

use <parts.scad>

module lower_mount(loc_res = 32) {
    // 3d print mount
    // lower 5 mm spindle holder
    difference() {
        union() {
            hull() {
                translate([0, 0, 41])
                cylinder(d = 10, h = 18, $fn = loc_res);
                translate([-6, 0, 41])
                cylinder(d = 10, h = 18, $fn = loc_res);
            }
            // upper base plate + holder
            translate([-16, -43/2, 41+16])
            cube([24, 43, 3]); 
            // upper fromt
            translate([-16, -43/2, 41+16])
            cube([3, 43, 44]);
            hull() {
                translate([-16, -43/2-2, 41+16])
                cube([24, 2, 3]); 
                translate([-16, -43/2-2, 41+16])
                cube([3, 2, 44]);
            }
            hull() {
                translate([-16, 43/2, 41+16])
                cube([24, 2, 3]); 
                translate([-16, 43/2, 41+16])
                cube([3, 2, 44]);
            }
            
        }
        // cut mounting holes and screw
        translate([0, 0, 40])
        cylinder(d = 5.5, h = 17, $fn = loc_res);
        translate([0, 0, 50])
        rotate([0, -90, 0])
        cylinder(d = 3.5, h = 20, $fn = loc_res);
        // cut m3 counter nut
        hull() {
            translate([-8, 0, 50])
            rotate([0, 90, 0])
            cylinder(d = 7.0, h = 3, $fn = 6);
            translate([-8, 0, 70])
            rotate([0, 90, 0])
            cylinder(d = 7.0, h = 3, $fn = 6);
        }
        // mounting position for upper motor
        rotate([0, 0, 180])
        translate([10, 0, 60+22])
        rotate([0, 90, 0])
        nema17_top_cut(loc_res = loc_res);
    }
}

module sensor_mount(loc_res = 32) {
    // 3d print mount
    // lower 5 mm spindle holder
    rotate([90, 0, 0])
    translate([0, 0, -41])
    difference() {
        union() {
            hull() {
                translate([0, 0, 41])
                cylinder(d = 10, h = 18, $fn = loc_res);
                translate([-6, 0, 41])
                cylinder(d = 10, h = 18, $fn = loc_res);
            }
            
        }
        // cut mounting holes and screw
        translate([0, 0, 40])
        cylinder(d = 5.5, h = 17, $fn = loc_res);
        translate([0, 0, 50])
        rotate([0, -90, 0])
        cylinder(d = 3.5, h = 20, $fn = loc_res);
        // cut m3 counter nut
        hull() {
            translate([-8, 0, 50])
            rotate([0, 90, 0])
            cylinder(d = 7.0, h = 3, $fn = 6);
            translate([-8, 0, 70])
            rotate([0, 90, 0])
            cylinder(d = 7.0, h = 3, $fn = 6);
        }
    }
    *translate([10, -30, -14.5/2])
    rotate([90, 0, 90])
    pcb_vl53l1x_satel_cut_bottom(loc_res = loc_res);
    
    translate([5.5/2, -30, -16/2])
    cube([4, 30, 16]);
}

module put_together(show_elements = 1, loc_res = 32) {
    if(show_elements) {
        translate([0, 0, 0])
        rotate([0, 0, 180])
        nema17(loc_res = loc_res);
        rotate([0, 0, 180])
        translate([-20, 0, 60+22])
        rotate([0, 90, 0])
        nema17(loc_res = loc_res);
    }
    lower_mount(loc_res = loc_res);
    sensor_mount(loc_res = loc_res);
}

*put_together(1, 128);


*sensor_mount(128); // print 1x
lower_mount(128); // print 1x