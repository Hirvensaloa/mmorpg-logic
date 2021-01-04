#include "../common.h"

Map::Map(const std::vector<std::shared_ptr<Grid>>& grids)
	: _grids(grids) 
{
	Log::PrintCreation<Map>(*this);
}

void Map::Update() const
{
	std::for_each(_grids.begin(), _grids.end(),
		[&](const std::shared_ptr<Grid>& grid) { grid->Update(); });

}

std::ostream& operator<<(std::ostream& os, const Map& map)
{
	os << "Map containing grids:\n";

	std::for_each(map._grids.cbegin(), map._grids.cend(),
		[&](const std::shared_ptr<Grid>& grid)
		{
			os << *grid << std::endl; 
		}
	);

	return os; 
}

std::shared_ptr<Grid> Map::GetGrid(const std::string& name) const
{

	const std::string lower = Util::toLower(name);

	auto it = std::find_if(_grids.cbegin(), _grids.cend(),
		[&](const std::shared_ptr<Grid>& grid)
		{
			return grid->GetName() == lower; 
		}
	);

	if (it != _grids.cend())
	{
		return *it;
	}
	else
	{
		return nullptr; 
	}
}

const std::vector<std::shared_ptr<Entity>> Map::GetNpcs() const
{
	std::vector<std::shared_ptr<Entity>> entities;

	std::for_each(_grids.begin(), _grids.end(),
		[&](const std::shared_ptr<Grid>& grid)
		{
			auto ent = grid->GetEntities();
			std::for_each(ent.begin(), ent.end(),
				[&](const std::shared_ptr<Entity>& ent)
				{
					if(ent->GetType() != Entity::entType::player)
						entities.push_back(ent);
				}
			);
		}
	);

	return entities; 
}
