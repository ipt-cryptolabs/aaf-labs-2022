let input = "";

function stdinLineByLine() {
    return new Promise(resolve => {
        console.log("Enter command: " + "\n")
        let lines = '';
        let buff = '';
        process.stdin
            .on('data', data => {
                buff += data;
                lines = buff.split(/\r\n|\n/).join(' ');
                input += lines;
                buff = "";
                if(lines[lines.length - 2] === ';'){
                    process.stdin.emit('end');
                }
            })
            .on('end', () => {
                resolve(input);
                process.stdin.destroy();
            });
    });
}

module.exports = stdinLineByLine;

