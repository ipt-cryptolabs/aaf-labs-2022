function create(arg){
    console.log("CREATE COLLECTION: " + arg);
}

function insert(arg1, arg2){
    console.log("INSERT " + "VALUE: " + arg2 + " IN COLLECTION: " + arg1);
}

function print_index(arg){
    console.log("PRINT INDEX OF COLLECTION: " + arg);
}

function search(arg){
    console.log("SEARCH IN COLLECTION: " + arg);
}

function searchWhere(arg1, arg2){
    console.log("SEARCH IN COLLECTION: " + arg1 + " WHERE " + arg2);
}

function searchWhereDash(arg1, arg2, arg3){
    console.log("SEARCH IN COLLECTION: " + arg1 + " WHERE " + arg2 + " - " + arg3);
}

function searchWhereHooks(arg1, arg2, arg3, arg4){
    console.log("SEARCH IN COLLECTION: " + arg1 + " WHERE " + arg2 + " <" + arg3 + "> " + arg4);
}

module.exports = {create, insert, print_index, search, searchWhere, searchWhereDash, searchWhereHooks};