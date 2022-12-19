bodies = {}
walls = {}
colors = {}
box_count = 100
box_size = 50
local texture = ContentManager:load_texture("screen.png")

function _init()
    for i = 0, box_count do
        bodies[i] = Physics.Body(PhysicsWorld, Vector2(math.random(0, 1024), math.random(0, 50)),
            Physics.RectangleColliderShape(box_size, box_size), 2)
        colors[i] = Color(math.random(0, 255), math.random(0, 255), math.random(0, 255))
    end
    walls[0] = Physics.Body(PhysicsWorld, Vector2(Graphics.screen_width / 2, 500),
        Physics.RectangleColliderShape(Graphics.screen_width, 50), 0)
end

-- floor:get_position()
function _update()
    for i = 0, box_count do
        Graphics:draw_texture_ex(bodies[i]:get_position() - Vector2(box_size / 2, box_size / 2),
            Vector2(box_size, box_size), bodies[i]:get_rotation(), texture)
        -- Graphics:draw_rect(bodies[i]:get_position() - Vector2(10, 10), Vector2(20, 20), colors[i])
    end
    Graphics:draw_rect(walls[0]:get_position() - Vector2(Graphics.screen_width, 50) / 2,
        Vector2(Graphics.screen_width, 50), Color(255, 0, 255))

end
