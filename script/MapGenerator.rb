##
## EPITECH PROJECT, 2018
## OOP_indie_studio_2018
## File description:
## script/MapGenerator.rb
##

class MapGenerator
    attr_accessor :size

    def initialize(arguments)
        @size = arguments[0].to_i
        @map = Array.new(@size) {|index|
            if (index == 0)
                Array.new(@size) {|index| 1}
            else
                Array.new(@size) {|index| 2}
            end
        }
    end

    def mapCorner()
        cornerPos = [
            [0, 0],
            [0, 1],
            [1, 0],
            [0, @size - 1],
            [0, @size - 2],
            [1, @size - 1],
            [@size - 1, 0],
            [@size - 1, 1],
            [@size - 2, 0],
            [@size - 1, @size - 1],
            [@size - 1, @size - 2],
            [@size - 2, @size - 1]
        ]

        cornerPos.each do |coord|
            @map[coord[0]][coord[1]] = 0
        end
    end

    def breakWall()
        0.upto(@size * 3) do |i|
            x = Random.rand(@size - 1)
            y = Random.rand(@size - 1)
            @map[y][x] = 1 if @map[y][x] == 2
        end
    end

    def addRow(x, y)
        rowSize = Random.rand(@size - x)
        openPos = Random.rand(rowSize + 1)

        x.upto(x + rowSize) do |pos|
            @map[y][pos] = 1
        end
        if (rowSize == 0 && @map[y - 2][x] == 2)
            @map[y][x - 1] = 1;
        else
            while (@map[y - 2][x + openPos] == 2)
                openPos = Random.rand(rowSize + 1)
            end
            @map[y - 1][x + openPos] = 1
        end
        return (x + rowSize + 2)
    end

    def generate()
        y = 2
        x = 0

        if (@size > 2)
            until y > @size - 1
                until x > @size - 1
                    x = addRow(x, y)
                end
                y += 2
                x = 0
            end
        end
        mapCorner()
        breakWall()
    end

    def sendMap()
        @map.each do |line|
            line.each do |chr|
                print chr
            end
            puts
        end
    end
end

mapGen = MapGenerator.new(ARGV)
mapGen.generate()
mapGen.sendMap()
