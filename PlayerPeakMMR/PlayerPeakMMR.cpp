#include "pch.h"
#include "PlayerPeakMMR.h"

#include <string>

BAKKESMOD_PLUGIN(PlayerPeakMMR, "Peak MMR", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

void PlayerPeakMMR::onLoad()
{
	_globalCvarManager = cvarManager;
	LOG("Welcome to Player Peak MMR plugin");
	// !! Enable debug logging by setting DEBUG_LOG = true in logging.h !!
	//DEBUGLOG("PlayerPeakMMR debug mode enabled");

	// LOG and DEBUGLOG use fmt format strings https://fmt.dev/latest/index.html
	//DEBUGLOG("1 = {}, 2 = {}, pi = {}, false != {}", "one", 2, 3.14, true);

	//cvarManager->registerNotifier("my_aweseome_notifier", [&](std::vector<std::string> args) {
	//	LOG("Hello notifier!");
	//}, "", 0);

	//auto cvar = cvarManager->registerCvar("template_cvar", "hello-cvar", "just a example of a cvar");
	//auto cvar2 = cvarManager->registerCvar("template_cvar2", "0", "just a example of a cvar with more settings", true, true, -10, true, 10 );

	//cvar.addOnValueChanged([this](std::string cvarName, CVarWrapper newCvar) {
	//	LOG("the cvar with name: {} changed", cvarName);
	//	LOG("the new value is: {}", newCvar.getStringValue());
	//});

	//cvar2.addOnValueChanged(std::bind(&PlayerPeakMMR::YourPluginMethod, this, _1, _2));

	// enabled decleared in the header
	//enabled = std::make_shared<bool>(false);
	//cvarManager->registerCvar("TEMPLATE_Enabled", "0", "Enable the TEMPLATE plugin", true, true, 0, true, 1).bindTo(enabled);

	//cvarManager->registerNotifier("NOTIFIER", [this](std::vector<std::string> params){FUNCTION();}, "DESCRIPTION", PERMISSION_ALL);
	//cvarManager->registerCvar("CVAR", "DEFAULTVALUE", "DESCRIPTION", true, true, MINVAL, true, MAXVAL);//.bindTo(CVARVARIABLE);
	//gameWrapper->HookEvent("FUNCTIONNAME", std::bind(&TEMPLATE::FUNCTION, this));
	//gameWrapper->HookEventWithCallerPost<ActorWrapper>("FUNCTIONNAME", std::bind(&PlayerPeakMMR::FUNCTION, this, _1, _2, _3));
	//gameWrapper->RegisterDrawable(bind(&TEMPLATE::Render, this, std::placeholders::_1));


	//gameWrapper->HookEvent("Function TAGame.Ball_TA.Explode", [this](std::string eventName) {
	//	LOG("Your hook got called and the ball went POOF");
	//});
	// You could also use std::bind here
	//gameWrapper->HookEvent("Function TAGame.Ball_TA.Explode", std::bind(&PlayerPeakMMR::YourPluginMethod, this);

	gameWrapper->HookEvent("Function GameEvent_TA.Countdown.BeginState", std::bind(&PlayerPeakMMR::gameStart, this));
}

void PlayerPeakMMR::onUnload() {
	LOG("See you in Player Peak MMR plugin !");
}

void PlayerPeakMMR::gameStart() {
	ServerWrapper server = gameWrapper->GetCurrentGameState();
	if (!server) { return; }

	//check if 5 minutes remaining
	if (server.GetSecondsRemaining() == 300)
	{
		getAllPlayers(server);
	}

}

void PlayerPeakMMR::getAllPlayers(ServerWrapper server) {

	LOG("getAllPlayers() function");

	//if (!gameWrapper->IsInFreeplay()) { return; }

	auto cars = server.GetCars();
	if (cars.Count() == 0){ LOG("No cars found"); }

	for (auto Car : cars) {

		auto pris = Car.GetPRI();
		auto platformString = knowPlatform(pris.GetPlatform());

		LOG("Platform : " + platformString);
		LOG("Name : " + pris.GetPlayerName().ToString());


		switch (pris.GetPlatform()) {
			case OnlinePlatform_Unknown:
				LOG("Unknow : " + pris.GetUniqueIdWrapper().GetIdString());
				break;
			case OnlinePlatform_Steam:
				LOG("Steam ID : " + pris.GetUniqueIdWrapper().GetIdString());
				//LOG("Steam ID 2 : " + std::to_string(pris.GetUniqueId().ID));
				break;
			case OnlinePlatform_PS4:
				LOG("PS4 : " + pris.GetUniqueIdWrapper().GetIdString());
				break;
			case OnlinePlatform_PS3:
				LOG("PS3 : " + pris.GetUniqueIdWrapper().GetIdString());
				break;
			case OnlinePlatform_PsyNet:
				LOG("PsyNet : " + pris.GetUniqueIdWrapper().GetIdString());
				break;
			case OnlinePlatform_Epic:
				LOG("Epic ID : " + pris.GetUniqueIdWrapper().GetEpicAccountID());
				break;
			default:
				LOG("Default");
				break;
			}
		
	}

}

string PlayerPeakMMR::knowPlatform(OnlinePlatform online) {
	switch (online) {
		case OnlinePlatform_Unknown:
			return "Unknown";
		case OnlinePlatform_Steam:
			return "Steam";
		case OnlinePlatform_PS4:
			return "PS4";
		case OnlinePlatform_PS3:
			return "PS3";
		case OnlinePlatform_Dingo:
			return "Dingo";
		case OnlinePlatform_QQ:
			return "QQ";
		case OnlinePlatform_OldNNX:
			return "Old NNX";
		case OnlinePlatform_NNX:
			return "NNX";
		case OnlinePlatform_PsyNet:
			return "PsyNet";
		case OnlinePlatform_Deleted:
			return "Deleted";
		case OnlinePlatform_WeGame:
			return "WeGame";
		case OnlinePlatform_Epic:
			return "Epic";
		case OnlinePlatform_MAX:
			return "Max";
		default:
			return "Unknown";
		}
}
