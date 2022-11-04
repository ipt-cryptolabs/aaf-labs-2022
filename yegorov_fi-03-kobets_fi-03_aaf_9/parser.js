const input = require('./input');
const commands = require('./commands');
const fs = require('fs');

let commandLog = JSON.parse(fs.readFileSync('./log/commandLog.json', 'utf8'));

const createReg = /^CREATE+\s+\b[a-zA-Z0-9_]+\b$/i;
const insertReg = /^INSERT+\s+[a-zA-Z0-9_]+\s+"+[^"]+"$/i;
const print_indexReg = /^PRINT_INDEX+\s+\b[a-zA-Z0-9_]+\b$/i;
const searchReg = /^SEARCH+\s+\b[a-zA-Z0-9_]+\b$/i;
const searchRegWhere = /^SEARCH+\s+[a-zA-Z0-9_]+\s+WHERE+\s+"+[^"]+"$/i;
const searchWhereDashReg = /^SEARCH+\s+[a-zA-Z0-9_]+\s+WHERE+\s+"+[^"]+"+\s+-+\s+"+[^"]+"$/i;
const searchWhereHooksReg = /^SEARCH+\s+[a-zA-Z0-9_]+\s+WHERE+\s+"+[^"]+"+\s+<+\d+>+\s+"+[^"]+"$/i;
const hooksReg = /<+\d+>/;

function ifValid(str){
    if(createReg.test(str))
        return 0;
    if(insertReg.test(str))
        return 1;
    if(print_indexReg.test(str))
        return 2;
    if(searchReg.test(str))
        return 3;
    if(searchRegWhere.test(str))
        return 4;
    if(searchWhereDashReg.test(str))
        return 5;
    if(searchWhereHooksReg.test(str))
        return 6;

    throw new Error("INVALID INPUT");
}

input().then(input => {
    let tokens = [];
    let token = ""
    try {
        for (let i = 0; i < input.length; i++) {
            if (input[i] === " " || input[i] === ";") {
                tokens.push(token);
                token = "";
            } else {
                token += input[i];
            }
        }
        tokens = tokens.filter(tokens => tokens !== "");

        switch(ifValid(tokens.join(" "))){
            case 0:
                commands.create(tokens[1]);
                commandLog.command.push("CREATE COMMAND");
                break;
            case 1:
                commands.insert(tokens[1], tokens.slice(2,));
                commandLog.command.push("INSERT COMMAND");
                break;
            case 2:
                commands.print_index(tokens[1]);
                commandLog.command.push("PRINT_INDEX COMMAND");
                break;
            case 3:
                commands.search(tokens[1]);
                commandLog.command.push("SEARCH COMMAND");
                break;
            case 4:
                commands.searchWhere(tokens[1], tokens.slice(3));
                commandLog.command.push("SEARCH WHERE COMMAND");
                break;
            case 5:
                let dashIndex = tokens.indexOf('-');

                commands.searchWhereDash(tokens[1], tokens.slice(3, dashIndex), tokens.slice(dashIndex+1, ));
                commandLog.command.push("SEARCH WHERE_DASH COMMAND");
                break;
            case 6:
                let numInHooks;

                tokens.forEach((token) => {
                    if(hooksReg.test(token)){
                        numInHooks = token;
                    }
                });

                let numInHooksIndex = tokens.indexOf(numInHooks);

                commands.searchWhereHooks(tokens[1], tokens.slice(3,numInHooksIndex), numInHooks.slice(1, numInHooks.length-1), tokens.slice(numInHooksIndex+1, ));
                commandLog.command.push("SEARCH WHERE_HOOKS COMMAND");
                break;
        }
        console.log(tokens);
        fs.writeFileSync('./log/commandLog.json', JSON.stringify(commandLog));
    }catch(error){
        commandLog.command.push("INVALID COMMAND");
        fs.writeFileSync('./log/commandLog.json', JSON.stringify(commandLog));
        console.log(error);
    }
});

