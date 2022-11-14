const collections = {};

class Collection {
    constructor(name, id) {
        this.name = name;
        this.id = id;
        this.index = {};
        this.content = {};
    }
}

function collectionIndex(content, id, contentId) {
    let words = content.match(/\b(\w+)\b/g);

    for (let word of words) {
        if (word in collections[id].index) {
            if (!(contentId in collections[id].index[word])) collections[id].index[word][contentId] = [];
            collections[id].index[word][contentId].push(words.indexOf(word).toString());
            words[words.indexOf(word)] = "";
        } else {
            collections[id].index[word] = {};
            collections[id].index[word][contentId] = [words.indexOf(word).toString()];
            words[words.indexOf(word)] = "";
        }
    }
}

function ifExist(colName) {
    for (let id in collections) {
        if (collections[id].name === colName) return true;
    }
}

function getColIdByName(colName) {
    for (let id in collections) {
        if (collections[id].name === colName) return id; else console.log("no match")
    }
}

function create(colName) {
    console.log("CREATE COLLECTION: " + colName);
    if (ifExist(colName)) {
        console.log("Collection with name", colName, "already exists")
        return;
    }

    let id = Object.keys(collections).length;
    collections[id] = new Collection(colName, id);
    console.log(collections);
}

function insert(colName, content) {
    console.log("INSERT " + "VALUE: " + content + " IN COLLECTION: " + colName);
    if (!ifExist(colName)) {
        console.log("collection", colName, "doesnt exist");
        return;
    }

    let id = getColIdByName(colName);
    let contentId = Object.keys(collections[id].content).length;
    collections[id].content[contentId] = content;
    collectionIndex(content, id, contentId);
    console.log(collections);
}

function print_index(colName) {
    console.log("PRINT INDEX OF COLLECTION: " + colName);
    if (!ifExist(colName)) {
        console.log("collection", colName, "doesnt exist");
        return;
    }

    let id = getColIdByName(colName);
    console.log(collections[id].index);
}

function search(colName) {
    console.log("SEARCH IN COLLECTION: " + colName);
    if (!ifExist(colName)) {
        console.log("collection", colName, "doesnt exist");
        return;
    }

    let id = getColIdByName(colName);

    for (let contentId in collections[id].content) {
        console.log(collections[id].content[contentId]);
    }
}

function searchWhere(colName, query) {
    console.log("SEARCH IN COLLECTION: " + colName + " WHERE " + query);
    if (!ifExist(colName)) {
        console.log("collection", colName, "doesnt exist");
        return;
    }

    let flag = false;
    let id = getColIdByName(colName);
    query = query.replaceAll('"', '');

    if (query.endsWith('*')) {
        query = query.replace('*', '');

        for (let word in collections[id].index) {
            if(word.toLowerCase().startsWith(query.toLowerCase())){
                flag = true;
                for(let colId in collections[id].index[word]){
                    console.log(collections[id].content[colId]);
                }
            }
        }
    } else {
        for (let word in collections[id].index) {
            if(word.toLowerCase() === query.toLowerCase()){
                flag = true;
                for(let colId in collections[id].index[word]){
                    console.log(collections[id].content[colId]);
                }
            }
        }
    }

    if(!flag)
        console.log("nothing found");
}

function searchWhereDash(arg1, arg2, arg3) {
    console.log("SEARCH IN COLLECTION: " + arg1 + " WHERE " + arg2.join(" ") + " - " + arg3.join(" "));
}

function searchWhereHooks(arg1, arg2, arg3, arg4) {
    console.log("SEARCH IN COLLECTION: " + arg1 + " WHERE " + arg2.join(" ") + " <" + arg3 + "> " + arg4.join(" "));
}

module.exports = {create, insert, print_index, search, searchWhere, searchWhereDash, searchWhereHooks};