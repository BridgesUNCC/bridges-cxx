#ifndef GAME_BASE_3D_H
#define GAME_BASE_3D_H

#include <SocketConnection.h>
#include "Bridges.h"
#include "Scene.h"



namespace bridges {
	namespace game {
		/**
		 * @brief This class extends the GameBase class to 3D environments
		 *
		 *  This class  forms the infrastructure for the BRIDGES Game API and
		 *  contains methods for input listener and drawing functions and attributes
		 *
		 * @author Kalpathi Subramanian, Matthew Mcquaigue
		 * @date 9/27/22
		 *
		 */

		class GameBase {
			private:
				Bridges bridges;

				GameGrid gg;

				bool firsttime = true;

				bool bquit = false;
				std::unique_ptr<SocketConnection> sockcon;

			protected:
				bool debug = false;


				/**
				 *  @brief Protected constructed prevens direct creation
				 *
				 * Having a protected constructor prevents the object from being
				 * directly created. Since GameBase is meant to be a
				 * purely internal class, that seems appropriate.
				 */
				GameBase(int assignmentID, std::string username, std::string apikey)
								: bridges(assignmentID, username, apikey), 

					bridges.setServer("games");
				  
					sockcon = std::make_unique<SocketConnection>(bridges);

					// set up the default 3D scene
					scene = Scene({'fov': 90, 'type': 'fps', 'position': [0.0, 0.0, 0.0]})
				}

		  virtual ~GameBase3D() =default;

				/// @brief This function is called once when the game starts.
				///
				/// Students write this function.
				/// It will be called once at the begining of the game.
				virtual void initialize () = 0;

				/// @brief This function is called once per frame of the game.
				///
				/// Students write this function.
				/// It will be called at each frame of the game.

				virtual void gameLoop () = 0;


			protected:
				/// @brief register a new KeypressListener
				///
				/// Students should not have to call this function directly.  The
				/// KeypressListener listener will get notified of all keypresses
				/// (up and down) that happens in the game.
				///
				/// @param p a KeypressListener to register
				void registerKeyListener(KeypressListener* p) {
					sockcon->registerKeyListener(p);
				}

				/// @brief Renders the game
				///
				/// Student should not have to call this function directly. It is
				/// called automatically by Bridges.
				void render() {
					if (firsttime) {
						bridges.setJSONFlag(debug);

						bridges.setDataStructure(&scene);

						bridges.visualize();

						firsttime = false;
					}
					scene_state = scene.getDataStructureRepresentation();

					sockcon->sendSceneData(scene_state);
				}

			protected:

				///@brief calling this function causes the game to end.
				///
				///That is to say, the current frame will be the last frame of the
				///game.
				void quit() {
					bquit = true;
				}


				/// @brief Set the title of the game
				///
				/// @param title Title of the game
				void setTitle(std::string title) {
					bridges.setTitle(title);
				}

				/// @brief Set a short description of the game
				///
				/// @param desc Description of the game
				void setDescription(std::string desc) {
					bridges.setDescription(desc);
				}
		};
}

#endif
