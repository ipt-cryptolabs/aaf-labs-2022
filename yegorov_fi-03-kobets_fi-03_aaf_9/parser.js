const input = require('./input');
const commands = require('./commands');

let createReg = /CREATE+\s+\b[a-zA-Z0-9_]+\b$/i;
let insertReg = /INSERT+\s+[a-zA-Z0-9_]+\s+\B"\b[a-zA-Z0-9_]+\b"+\B$/i;
let print_indexReg = /PRINT_INDEX+\s+\b[a-zA-Z0-9_]+\b$/i;
let searchReg = /SEARCH+\s+\b[a-zA-Z0-9_]+\b$/i;
let searchRegWhere = /SEARCH+\s+[a-zA-Z0-9_]+\s+WHERE+\s+\b[a-zA-Z0-9_]+\b$/i;
let searchWhereDashReg = /SEARCH+\s+[a-zA-Z0-9_]+\s+WHERE+\s+\b[a-zA-Z0-9_]+\s+-+\s+[a-zA-Z0-9_]+\b$/i;
let searchWhereHooksReg = /SEARCH+\s+[a-zA-Z0-9_]+\s+WHERE+\s+\b[a-zA-Z0-9_]+\s+<+\d+>+\s+[a-zA-Z0-9_]+\b$/i;

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
        console.log(tokens);
        switch(ifValid(tokens.join(" "))){
            case 0:
                commands.create(tokens[1]);
                break;
            case 1:
                commands.insert(tokens[1], tokens[2]);
                break;
            case 2:
                commands.print_index(tokens[1]);
                break;
            case 3:
                commands.search(tokens[1]);
                break;
            case 4:
                commands.searchWhere(tokens[1], tokens[3]);
                break;
            case 5:
                commands.searchWhereDash(tokens[1], tokens[3], tokens[5]);
                break;
            case 6:
                commands.searchWhereHooks(tokens[1], tokens[3], tokens[4][1], tokens[5]);
                break;
        }
    }catch(error){
        console.log(error);
    }
});

