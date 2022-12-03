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
            collections[id].index[word][contentId].push(words.indexOf(word));
            words[words.indexOf(word)] = "";
        } else {
            collections[id].index[word] = {};
            collections[id].index[word][contentId] = [words.indexOf(word)];
            words[words.indexOf(word)] = "";
        }
    }
}

function ifExist(colName) {
    for (let id in collections) {
        if (collections[id].name === colName)
            return true;
    }
}

function getColIdByName(colName) {
    for (let id in collections) {
        if (collections[id].name === colName)
            return id;
    }
}

function create(colName) {
    if (ifExist(colName)) {
        console.log("CREATE FAILED: Collection with name ", colName, " already exists!")
        return;
    }

    console.log("CREATE COLLECTION: " + colName);

    let id = Object.keys(collections).length;
    collections[id] = new Collection(colName, id);
    console.log(collections);
}

function insert(colName, content) {
    if (!ifExist(colName)) {
        console.log("INSERT FAILED: Collection ", colName, " does not exist!");
        return;
    }

    console.log("INSERT " + "VALUE: " + content + " IN COLLECTION: " + colName);

    let id = getColIdByName(colName);
    let contentId = Object.keys(collections[id].content).length;
    collections[id].content[contentId] = content;
    collectionIndex(content, id, contentId);
    console.log(collections);
}

function print_index(colName) {
    if (!ifExist(colName)) {
        console.log("PRINT_INDEX FAILED: Collection ", colName, " does not exist!");
        return;
    }

    console.log("PRINT INDEX OF COLLECTION: " + colName);

    let id = getColIdByName(colName);

    for(let word in collections[id].index){
        console.log('"' + word + '":');
        for(let key in collections[id].index[word]){
            console.log("d" + key + " -> " + "[" + collections[id].index[word][key] + "]");
        }
    }
}

function search(colName) {
    if (!ifExist(colName)) {
        console.log("SEARCH FAILED: Collection ", colName, " does not exist!");
        return;
    }

    console.log("SEARCH IN COLLECTION: " + colName);

    let id = getColIdByName(colName);

    for (let contentId in collections[id].content) {
        console.log(collections[id].content[contentId]);
    }
}

function searchWhere(colName, query) {
    if (!ifExist(colName)) {
        console.log("SEARCH FAILED: Collection ", colName, " does not exist!");
        return;
    }

    console.log("SEARCH IN COLLECTION: " + colName + " WHERE " + query);

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
        console.log("SEARCH FAILED: Nothing found!");
}

function searchWhereDash(colName, query1, query2) {
    query1 = query1.replaceAll('"', '').toLowerCase();
    query2 = query2.replaceAll('"', '').toLowerCase();

    if (!ifExist(colName)) {
        console.log("SEARCH FAILED: Collection ", colName, " does not exist!");
        return;
    }

    console.log("SEARCH IN COLLECTION: " + colName + " WHERE " + query1 + " - " + query2);

    let id = getColIdByName(colName);
    let flag = false;

    let lowerCaseKeys = Object.keys(collections[id].index).map(key => key.toLowerCase());

    if(lowerCaseKeys.includes(query1) && lowerCaseKeys.includes(query2)){
        for(let word in collections[id].index) {
            if (word.toLowerCase() >= query1 && word.toLowerCase() <= query2) {
                for(let colId in collections[id].index[word]){
                    flag = true;
                    console.log(collections[id].content[colId]);
                }
            }
        }

        if(!flag)
            console.log("SEARCH FAILED: Nothing found!");
    }else{
        console.log("SEARCH FAILED: No such words!");
        return;
    }

}

function searchWhereHooks(colName, query1, param, query2) {
    query1 = query1.replaceAll('"', '').toLowerCase();
    query2 = query2.replaceAll('"', '').toLowerCase();

    if (!ifExist(colName)) {
        console.log("SEARCH FAILED: Collection ", colName, " does not exist!");
        return;
    }

    console.log("SEARCH IN COLLECTION: " + colName + " WHERE " + query1+ " <" + param + "> " + query2);

    let id = getColIdByName(colName);
    let flag = false;

    let lowerCaseKeys = Object.keys(collections[id].index).map(key => key.toLowerCase());

    if(lowerCaseKeys.includes(query1) && lowerCaseKeys.includes(query2)){
        let query1Index;
        let query2Index;

        for(let word in collections[id].index){
            if(word.toLowerCase() === query1){
                query1Index = collections[id].index[word];
            }
            if(word.toLowerCase() === query2){
                query2Index = collections[id].index[word];
            }
        }

        for(let colId in query1Index){
            if(Object.keys(query2Index).includes(colId)){
                let maxLength = Math.max(query1Index[colId].length, query2Index[colId].length);
                let maxLengthArr;
                let minLengthArr;

                if(query1Index[colId].length === maxLength){
                    maxLengthArr = query1Index[colId];
                    minLengthArr = query2Index[colId];
                }else{
                    maxLengthArr = query2Index[colId];
                    minLengthArr = query1Index[colId];
                }

                for(let i = 0; i < maxLength; i++){
                    for(let j = 0; j < minLengthArr.length; j++){
                        if(Math.abs(maxLengthArr[j] - minLengthArr[i]) === param){
                            flag = true;
                            console.log(collections[id].content[colId]);
                        }
                    }
                }
            }
        }

        if(!flag)
            console.log("SEARCH FAILED: Nothing found!");
    }else{
        console.log("SEARCH FAILED: No such words!");
        return;
    }
}

module.exports = {create, insert, print_index, search, searchWhere, searchWhereDash, searchWhereHooks};