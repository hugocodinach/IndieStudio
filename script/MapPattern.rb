##
## EPITECH PROJECT, 2018
## OOP_indie_studio_2018
## File description:
## script/MapPattern.rb
##

class MapPattern
    def initialize(args)
        @content = []
        @map = []
        @mapBonus = []
        srand(args[0].to_i)

        File.open("./script/mapFrag.txt") do |file|
            file.each_line do |line|
                @content.push(line)
            end
        end
        0.upto(19) do
            @mapBonus.push('00000000000000000000')
        end
    end

    def leftCorner(x, y)
        y.upto(y + 9) do |posY|
            @map.push(@content[posY][x..(x + 9)])
        end
    end

    def rightCorner(x, y, i)
        y.upto(y + 9) do |posY|
            @map[i] = @map[i] + @content[posY][x..(x + 9)]
            i += 1
        end
    end

    def proceduralGen()
        yTab = [0, 10, 20]

        leftCorner(0, yTab[Random.rand(3)])
        rightCorner(10, yTab[Random.rand(3)], 0)
        leftCorner(20, yTab[Random.rand(3)])
        rightCorner(30, yTab[Random.rand(3)], 10)
    end

    def distribBonus()
        bonusNb = 20
        randomValue = 0

        0.upto(19) do |y|
            randomValue = Random.rand(20)
            while (@map[y][randomValue] != '1')
                randomValue = Random.rand(20)
            end
            @mapBonus[y][randomValue] = '4'
        end
    end

    def sendMap()
        puts @map
        # puts
        # puts @mapBonus
    end
end

creator = MapPattern.new(ARGV)
creator.proceduralGen()
creator.distribBonus()
creator.sendMap()
