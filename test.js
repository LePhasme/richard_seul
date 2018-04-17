const inquirer = require('inquirer')
const SerialPort = require('serialport')

let board = new SerialPort('COM3', { // Remplacer COM3 avec le bon port, tel qu'il est affiché par l'application Arduino
    baudRate: 115200
})
let asking = false
let boardData = ''
let boardOpened = false
let noReturnTimer = null

board.on('error', function(err) {
    console.log('Erreur du contrôleur :')
    console.log(err)
})

board.on('open', function() {
    boardOpened = true
    console.log('Contrôleur ouvert !')
})

board.on('data', function(data) {
    boardData += data.toString().trim()
    let indexEnd = boardData.indexOf(']')
    if (indexEnd !== -1) {
        let indexStart = boardData.indexOf('[')
        if (indexStart !== -1) {
            if (indexStart < indexEnd) {
                boardData = boardData.substr(indexStart, indexEnd - indexStart + 1)
                if (boardData.indexOf('ok') !== -1 && asking === false) {
                    clearTimeout(noReturnTimer)
                    ask()
                }
                boardData = ''
            } else {
                boardData = boardData.substr(indexStart)
            }
        } else {
            boardData = ''
        }
    }
})

function noReturn() {
    console.log('Pas de réponse du contrôleur !')
    ask()
}

function ask() {
    asking = true
    inquirer.prompt([{
        type: 'list',
        name: 'command',
        message: 'Choisir une action',
        choices: [{
            name: 'Déplacer les roues',
            value: 'wheel'
        }, {
            name: 'Déplacer le vérin',
            value: 'verin'
        }, {
            name: 'Déplacer les deux',
            value: 'both'
        }, {
            name: 'Quitter',
            value: 'quit'
        }]
    }]).then(answers => {
        asking = false
        switch (answers.command) {
            case 'wheel':
            case 'verin':
            case 'both':
                console.log('Envoi de la commande...')
                board.write('[' + answers.command + ']\r\n')
                noReturnTimer = setTimeout(noReturn, 30 * 1000) // On attend un retour pendant 30 secondes max...
                break
            case 'quit':
                console.log('Bye.')
                if (boardOpened === true) {
                    board.close()
                }
                break
        }
    })
}

setTimeout(ask, 1000)
