let input = "";
// let commands = [];
function stdinLineByLine() {
    return new Promise(resolve => {
        console.log("Enter command: " + "\n")
        let lines = '';
        let buff = '';
        process.stdin
            .on('data', data => {
                buff += data;
                //console.log("buff: " + buff);
                lines = buff.split(/\r\n|\n/).join(' ');
                //console.log("lines: " + lines);
                input += lines;
                buff = "";
                if(lines[lines.length - 2] === ';'){
                    process.stdin.emit('end');
                }
            })
            .on('end', () => {
                //console.log(input);
                resolve(input);
                process.stdin.destroy();
            });
    });
}

module.exports = stdinLineByLine;

