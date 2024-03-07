"use strict";

const fs = require("fs");
const path = require("path");

const pakdata = fs.readFileSync("./build/bme.zip");

let buf = Buffer.alloc(4*4 + 128*4*4);
let offset = 0;

offset = buf.write("rBSP", offset, "ascii"); // magic
offset = buf.writeUInt32LE(29, offset); // version
offset = buf.writeUInt32LE(6, offset); // revision
offset = buf.writeUInt32LE(127, offset);

let lump40def_offset;

for (let i = 0; i < 128; i++) {
    if (i === 40) {
        lump40def_offset = offset;
    }
    offset = buf.writeUInt32LE(0, offset); // offset
    offset = buf.writeUInt32LE(0, offset); // length
    offset = buf.writeUInt32LE(0, offset); // version
    offset = buf.writeUInt32LE(0, offset); // char	fourCC[4];	// lump ident code
}

buf.writeUInt32LE(offset, lump40def_offset); // write current file offset as lump 40's offset
buf.writeUInt32LE(pakdata.length, lump40def_offset+4); // lump 40's length

buf = Buffer.concat([buf, pakdata, Buffer.alloc(pakdata.length % 16)]);

fs.writeFileSync("./installer/source/bme/bme.bsp", buf);


// Write file list to FilesystemContents.h for our dll

const walk = function(dir, done) {
    let results = [];
    fs.readdir(dir, function(err, list) {
        if (err) return done(err);
        let i = 0;
        (function next() {
            let file = list[i++];
            if (!file) return done(null, results);
            file = path.resolve(dir, file);
            //file = dir + '/' + file;
            fs.stat(file, function(err, stat) {
                if (stat && stat.isDirectory()) {
                    walk(file, function(err, res) {
                        results = results.concat(res);
                        next();
                    });
                } else {
                    results.push(file);
                    next();
                }
            });
        })();
    });
};

const dir = './r1_modsrc';
walk(dir, (err, results) => {
    results = results.map(r => r.replace(fs.realpathSync(dir), '')).map(r => r.replace(/\\/g, '/').replace(/^\//, ''));
    //console.log(results);
    let file = '';
    file += "#pragma once\n\n";
    file += "#define FILES_COMMA_SEPARATED " + results.map(r => '"'+r+'"').join(', ');
    fs.writeFileSync("./bmedll/FilesystemContents.h", file);
});
