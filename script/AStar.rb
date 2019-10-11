##
## EPITECH PROJECT, 2018
## OOP_indie_studio_2018
## File description:
## script/AStar.rb
##

class Node
    attr_accessor :x, :y, :parentX, :parentY, :quality, :step

    def initialize(x, y, parentX, parentY, quality, step)
        @x = x
        @y = y
        @parentX = parentX
        @parentY = parentY
        @quality = quality
        @step = step
    end
end

class AStar
    attr_accessor :finalList, :reachEnd

    def initialize(map, myX, myY, destX, destY)
        @map = map
        @destX = destX
        @destY = destY
        @openList = []
        @closeList = [Node.new(myX, myY, -1, -1, (@destX - myX).abs + (@destY - myY).abs, 0)]
        @finalList = []
        @posX = myX
        @posY = myY
        @reachEnd = false
    end

    def isClosedList(x, y)
        @closeList.each do |coord|
            if (coord.x == x && coord.y == y)
                return (1)
            end
        end
        return (0)
    end

    def tryPushOpen(x, y)
        @openList.each do |node|
            if (node.x == x && node.y == y)
                if (node.quality + node.step > (@destX - x).abs + (@destY - y).abs + @closeList[0].step + 1)
                    node.step = @closeList[0].step + 1
                    node.parentX = @posX
                    node.parentY = @posY
                end
                return
            end
        end
        @openList.push(Node.new(x, y, @posX, @posY, (@destX - x).abs + (@destY - y).abs, @closeList[0].step + 1))
    end

    def addTileOpen()
        if ((@posX > 0 && (@map[@posY][@posX - 1] == '0' || @map[@posY][@posX - 1] == '4')) && isClosedList(@posX - 1, @posY) == 0)
            tryPushOpen(@posX - 1, @posY)
        end
        if ((@posX < @map.size - 1 && (@map[@posY][@posX + 1] == '0' || @map[@posY][@posX + 1] == '4')) && isClosedList(@posX + 1, @posY) == 0)
            tryPushOpen(@posX + 1, @posY)
        end
        if ((@posY > 0 && (@map[@posY - 1][@posX] == '0' || @map[@posY - 1][@posX] == '4')) && isClosedList(@posX, @posY - 1) == 0)
            tryPushOpen(@posX, @posY - 1)
        end
        if ((@posY < @map.size - 1 && (@map[@posY + 1][@posX] == '0' || @map[@posY + 1][@posX] == '4')) && isClosedList(@posX, @posY + 1) == 0)
            tryPushOpen(@posX, @posY + 1)
        end
    end

    def addTileOpenAndClose()
        if ((@posX > 0 && @map[@posY][@posX - 1] != '2' && @map[@posY][@posX - 1] != '3') && isClosedList(@posX - 1, @posY) == 0)
            tryPushOpen(@posX - 1, @posY)
        end
        if ((@posX < @map.size - 1 && @map[@posY][@posX + 1] != '2' && @map[@posY][@posX + 1] != '3') && isClosedList(@posX + 1, @posY) == 0)
            tryPushOpen(@posX + 1, @posY)
        end
        if ((@posY > 0 && @map[@posY - 1][@posX] != '2' &&  @map[@posY - 1][@posX] != '3') && isClosedList(@posX, @posY - 1) == 0)
            tryPushOpen(@posX, @posY - 1)
        end
        if ((@posY < @map.size - 1 && @map[@posY + 1][@posX] != '2' && @map[@posY + 1][@posX] != '3') && isClosedList(@posX, @posY + 1) == 0)
            tryPushOpen(@posX, @posY + 1)
        end
    end

    def choosePath()
        min = -1
        result = nil

        @openList.each do |node|
            if (min == -1 || node.quality + node.step < min)
                min = node.quality + node.step
                result = node
            end
        end
        return 1 if (result == nil)
        @closeList.unshift(Node.new(result.x, result.y, result.parentX, result.parentY, result.quality, result.step))
        @posX = result.x
        @posY = result.y
        @openList.delete(result)
    end

    def findWay()
        if (@closeList[0].x == @destX && @closeList[0].y == @destY)
            @reachEnd = true
            return (0);
        end
        return (1);
    end

    def findCloser(objective)
        index = nil

        while (findWay() != 0)
            if (objective == true)
                addTileOpen()
            else
                addTileOpenAndClose()
            end
            if (choosePath() == 1)
                break
            end
        end
        index = @closeList[0]
        while (index.parentX != -1 && index.parentY != -1)
            @finalList.push(index)
            @closeList.each do |node|
                if (node.x == index.parentX && node.y == index.parentY)
                    index = node
                    break
                end
            end
        end
        @finalList.reverse!
    end
end