bodies = {}
colors = {}
box_count = 100;
local body = Physics.Body(PhysicsWorld, Vector2(0, 0), Physics.RectangleColliderShape(PhysicsWorld, 20, 20), 2)

local floor = Physics.Body(PhysicsWorld, Vector2(Graphics.screen_width / 2, 500),
    Physics.RectangleColliderShape(PhysicsWorld, Graphics.screen_width, 50), 0)
function _init()
    for i = 0, box_count do
        bodies[i] = Physics.Body(PhysicsWorld, Vector2(math.random(0, 1024), math.random(0, 50)),
            Physics.RectangleColliderShape(PhysicsWorld, 20, 20), 2)
        colors[i] = Color(math.random(0, 255), math.random(0, 255), math.random(0, 255))
    end
end

-- floor:get_position()
function _update()
    for i = 0, box_count do
        Graphics:draw_rect(bodies[i]:get_position() - Vector2(10, 10), Vector2(20, 20), colors[i])
    end
    Graphics:draw_rect(floor:get_position() - Vector2(Graphics.screen_width, 50) / 2 ,
        Vector2(Graphics.screen_width, 50), Color(255, 0, 255))
end
