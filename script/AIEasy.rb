##
## EPITECH PROJECT, 2018
## OOP_indie_studio_2018
## File description:
## script/AIEasy.rb
##

require './script/AStar'

class AIEasy
    def initialize(arguments)
        @map = arguments[0].split("-")
        @mapDanger = arguments[1].split("-")
        @posX = arguments[6].to_i
        @posY = arguments[7].to_i
        @otherPlayer = []
        @dangerArea = []
        @powerArea = []
        @safeArea = []
        @rangeBomb = arguments[2].to_i
        @wallPass = arguments[3].to_i
        @power = arguments[4].to_i
        @direction = arguments[5].to_i
        index = 8

        while (index != arguments.size)
            @otherPlayer.push([arguments[index].to_i, arguments[index + 1].to_i])
            index += 2
        end
    end

    def findDanger(x, y)
        (x + 1).upto(x + @rangeBomb) do |posX|
            break if (posX > 19 || (@map[y][posX] != '0' && @map[y][posX] != '4'))
            @dangerArea.push([y, posX])
        end
        (x - 1).downto(x - @rangeBomb) do |posX|
            break if (posX < 0 || (@map[y][posX] != '0' && @map[y][posX] != '4'))
            @dangerArea.push([y, posX])
        end
        (y + 1).upto(y + @rangeBomb) do |posY|
            break if (posY > 19 || (@map[posY][x] != '0' && @map[posY][x] != '4'))
            @dangerArea.push([posY, x])
        end
        (y - 1).downto(y - @rangeBomb) do |posY|
            break if (posY < 0 || (@map[posY][x] != '0' && @map[posY][x] != '4'))
            @dangerArea.push([posY, x])
        end
        @dangerArea.push([y, x])
    end

    def analyseSafe()
        startY = (@posY - 8 < 0) ? 0 : @posY - 8
        endY = (@posY + 8 > @map[0].size - 1) ? 19 : @posY + 8
        startX = (@posX - 8 < 0) ? 0 : @posX - 8
        endX = (@posX + 8 > @map[0].size - 1) ? 19 : @posX + 8

        startY.upto(endY) do |y|
            startX.upto(endX) do |x|
                if ((@map[y][x] == '0' || @map[y][x] == '4') && @dangerArea.include?([y, x]) == false)
                    @safeArea.push([y, x])
                end
            end
        end
    end

    def analyseDangerAndPower()
        0.upto(19) do |y|
            0.upto(19) do |x|
                if (@mapDanger[y][x] != '0')
                    @dangerArea.push([y, x])
                elsif (@map[y][x] == '4')
                    @powerArea.push([y, x])
                end
            end
        end
    end

    def sendDirection(nodeDirection)
        if (nodeDirection == nil || @mapDanger[nodeDirection.y][nodeDirection.x] == '1')
            puts "Stay"
        elsif (nodeDirection.x > @posX)
            puts "Right"
        elsif (nodeDirection.x < @posX)
            puts "Left"
        elsif (nodeDirection.y > @posY)
            puts "Down"
        else
            puts "Up"
        end
    end

    def tryPutBomb(aStarList, aggro, nodeDirection)
        if ((@safeArea.include?([aStarList[0].y, aStarList[0].x])) || 
        (aStarList.size >= 2 && @safeArea.include?([aStarList[1].y, aStarList[1].x]) && @mapDanger[aStarList[0].y][aStarList[0].x] != '1' && @mapDanger[aStarList[0].y][aStarList[0].x] != '2') ||
        (aStarList.size >= 3 && @safeArea.include?([aStarList[2].y, aStarList[2].x]) && @mapDanger[aStarList[0].y][aStarList[0].x] != '1' && @mapDanger[aStarList[0].y][aStarList[0].x] != '2' && @mapDanger[aStarList[1].y][aStarList[1].x] != '1' && @mapDanger[aStarList[1].y][aStarList[1].x] != '2') ||
        (aStarList.size >= 4 && @safeArea.include?([aStarList[3].y, aStarList[3].x]) && @mapDanger[aStarList[0].y][aStarList[0].x] != '1' && @mapDanger[aStarList[0].y][aStarList[0].x] != '2' && @mapDanger[aStarList[1].y][aStarList[1].x] != '1' && @mapDanger[aStarList[1].y][aStarList[1].x] != '2' && @mapDanger[aStarList[2].y][aStarList[2].x] != '2' && @mapDanger[aStarList[2].y][aStarList[2].x] != '3'))
            puts "Bomb"
        elsif (aggro == false)
            puts "Stay"
        elsif (@map[nodeDirection.y][nodeDirection.x] != '1')
            sendDirection(nodeDirection)
        else
            puts "Stay"
        end
    end

    def escapeDecision(aggro)
        aStarList = []
        aStarTmp = nil

        analyseSafe()
        if (@safeArea.size == 0)
            puts "Stay"
            return
        end
        @safeArea.each do |pos|
            aStarTmp = AStar.new(@map, @posX, @posY, pos[1], pos[0])
            if (@wallPass == 1)
                aStarTmp.findCloser(false)
            else
                aStarTmp.findCloser(true)
            end
            aStarList.push([aStarTmp.finalList, aStarTmp.reachEnd])
        end
        aStarList.delete_if {|aStar| aStar[1] == false}
        if (aStarList.size == 0 || aStarList[0][0].size == 0)
            puts "Stay"
            return
        end
        aStarList.sort_by! {|aStar| aStar[0].size}
        if (aggro == false)
            sendDirection(aStarList[0][0][0])
        else
            tryPutBomb(aStarList[0][0], false, nil)
        end
    end

    def aggroDecision(nodeDirection)
        aStarList = []
        aStarTmp = nil

        analyseSafe()
        if (@safeArea.size == 0)
            sendDirection(nodeDirection)
            return
        end
        @safeArea.each do |pos|
            aStarTmp = AStar.new(@map, @posX, @posY, pos[1], pos[0])
            aStarTmp.findCloser(true)
            aStarList.push([aStarTmp.finalList, aStarTmp.reachEnd])
        end
        aStarList.map {|aStar| aStarList.delete(aStar) if aStar[1] == false}
        if (aStarList.size == 0)
            sendDirection(nodeDirection)
            return
        end
        aStarList.sort_by! {|aStar| aStar[0].size}
        tryPutBomb(aStarList[0][0], true, nodeDirection)
    end

    def playerDecision(aStarSelection)
        if (@otherPlayer.include?([aStarSelection.reverse[0].x, aStarSelection.reverse[0].y]) == false)
            sendDirection(aStarSelection[0])
        elsif (@dangerArea.include?([aStarSelection.reverse[0].y, aStarSelection.reverse[0].x]) == true)
            sendDirection(aStarSelection[0])
        else
            findDanger(@posX, @posY)
            if (@dangerArea.include?([aStarSelection.reverse[0].y, aStarSelection.reverse[0].x]) == false)
                sendDirection(aStarSelection[0])
            else
                aggroDecision(aStarSelection[0])
            end
        end
    end

    def wallDecision(nodeDirection)
        if (@dangerArea.include?([@posY, @posX]) == true)
            escapeDecision(false)
        elsif ((@map[@posY][@posX] == '1' || @wallPass == 1) && @dangerArea.include?([nodeDirection.y, nodeDirection.x]) == false)
            sendDirection(nodeDirection)
        else
            findDanger(@posX, @posY)
            @dangerArea.uniq!
            escapeDecision(true)
        end
    end

    def aggroOnMeDecision(nodeDirection)
        countOne = 0
        countTwo = 0

        @otherPlayer.each do |player|
            if (@dangerArea.include?([player[1], player[0]]))
                countOne += 1
            end
        end
        findDanger(@posX, @posY)
        @dangerArea.uniq!
        @otherPlayer.each do |player|
            if (@dangerArea.include?([player[1], player[0]]))
                countTwo += 1
            end
        end
        if (countOne < countTwo)
            escapeDecision(true)
        elsif (nodeDirection != nil && @dangerArea.include?([nodeDirection.y, nodeDirection.x]) == false)
            sendDirection(nodeDirection)
        else
            puts "Stay"
        end
    end

    def chooseDestination()
        aStarTmp = nil 
        aStarFinal = []
        aStarPower = []

        @powerArea.each do |pos|
            aStarTmp = AStar.new(@map, @posX, @posY, pos[1], pos[0])
            aStarTmp.findCloser(true)
            aStarPower.push([aStarTmp.finalList, aStarTmp.reachEnd])
        end
        aStarPower.delete_if {|aStar| aStar[1] == false}
        aStarPower.sort_by! {|aStar| aStar[0].size}
        if (aStarPower.size != 0)
            return aStarPower[0][0]
        end
        @otherPlayer.each do |player|
            aStarTmp = AStar.new(@map, @posX, @posY, player[0], player[1])
            aStarTmp.findCloser(true)
            aStarFinal.push([aStarTmp.finalList, aStarTmp.reachEnd])
        end
        aStarFinal.delete_if {|aStar| aStar[1] == false}
        aStarFinal.sort_by! {|aStar| aStar[0].size}
        if (aStarFinal.size != 0)
            return aStarFinal[0][0]
        end
        @otherPlayer.each do |player|
            aStarTmp = AStar.new(@map, @posX, @posY, player[0], player[1])
            aStarTmp.findCloser(false)
            aStarFinal.push(aStarTmp.finalList)
        end
        aStarFinal.sort_by! {|aStar| aStar.size}
        if (aStarFinal.size() == 0)
            puts "Stay"
            exit(0)
        end
        return aStarFinal[0]
    end

    def useKick()
        if (@posX + 1 <= 19 && @map[@posY][@posX + 1] == '3' && @posX + 2 <= 19 && @map[@posY][@posX + 2] == '0')
            return true
        elsif (@posX - 1 >= 0 && @map[@posY][@posX - 1] == '3' && @posX - 2 >= 0 && @map[@posY][@posX - 2] == '0')
            return true
        elsif (@posY + 1 <= 19 && @map[@posY + 1][@posX] == '3' && @posY + 2 <= 19 && @map[@posY + 2][@posX] == '0')
            return true
        elsif (@posY - 1 >= 0 && @map[@posY - 1][@posX] == '3' && @posY - 2 >= 0 && @map[@posY - 2][@posX] == '0')
            return true
        end
        return false
    end

    def useStun()
        if (@posX + 1 <= 19 && @otherPlayer.include?([@posX + 1, @posY]) == true)
            return true
        elsif (@posX - 1 >= 0 && @otherPlayer.include?([@posX - 1, @posY]) == true)
            return true
        elsif (@posY + 1 <= 19 && @otherPlayer.include?([@posX, @posY + 1]) == true)
            return true
        elsif (@posY - 1 >= 0 && @otherPlayer.include?([@posX, @posY - 1]) == true)
            return true
        end
        return false
    end

    def useTeleport(aStarSelection)
        if (aStarSelection.size() < 2)
            return false
        elsif (@direction == 1 && aStarSelection[0].x == @posX + 1 && aStarSelection[1].x == @posX + 2 && (@map[@posY][aStarSelection[1].x] == '0' || @map[@posY][aStarSelection[1].x] == '4') && @dangerArea.include?([@posY, aStarSelection[1].x]) == false)
            return true
        elsif (@direction == 3 && aStarSelection[0].x == @posX - 1 && aStarSelection[1].x == @posX - 2 && (@map[@posY][aStarSelection[1].x] == '0' || @map[@posY][aStarSelection[1].x] == '4') && @dangerArea.include?([@posY, aStarSelection[1].x]) == false)
            return true
        elsif (@direction == 2 && aStarSelection[0].y == @posY + 1 && aStarSelection[1].y == @posY + 2 && (@map[aStarSelection[1].y][@posX] == '0' || @map[aStarSelection[1].y][@posX] == '4') && @dangerArea.include?([aStarSelection[1].y, @posX]) == false)
            return true
        elsif (@direction == 0 && aStarSelection[0].y == @posY - 1 && aStarSelection[1].y == @posY - 2 && (@map[aStarSelection[1].y][@posX] == '0' || @map[aStarSelection[1].y][@posX] == '4') && @dangerArea.include?([aStarSelection[1].y, @posX]) == false)
            return true
        end
        return false
    end

    def decision()
        aStarSelection = chooseDestination()
        aStarTmp = AStar.new(@map, @posX, @posY, 0, 0)

        if (@power == 0 && useKick() == true)
            puts "Special"
        elsif (@power == 1 && useStun() == true)
            puts "Special"
        elsif (@power == 2 && useTeleport(aStarSelection) == true)
            puts "Special"
        elsif (@otherPlayer.include?([@posX, @posY]) == true && @wallPass == 1)
            aStarTmp.findCloser(false)
            sendDirection(aStarTmp.finalList[0])
        elsif (@otherPlayer.include?([@posX, @posY]) == true && @dangerArea.include?([@posY, @posX]) == false)
            aggroOnMeDecision(nil)
        elsif (@otherPlayer.include?([@posX, @posY]) == true && @dangerArea.include?([@posY, @posX]) == true)
            escapeDecision(false)
        elsif (aStarSelection.size() == 0)
            puts "Stay"
        elsif (@map[aStarSelection[0].y][aStarSelection[0].x] == "1")
            wallDecision(aStarSelection[0])
        elsif (@dangerArea.include?([aStarSelection[0].y, aStarSelection[0].x]) == false)
            playerDecision(aStarSelection)
        elsif (@dangerArea.include?([@posY, @posX]) == false && @map[aStarSelection.reverse[0].y][aStarSelection.reverse[0].x] != '4')
            aggroOnMeDecision(aStarSelection[0])
        else
            escapeDecision(false)
        end
    end
end

ai = AIEasy.new(ARGV)
ai.analyseDangerAndPower()
ai.decision()