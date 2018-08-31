#ifndef TEAMMESSAGENTP_H
#define TEAMMESSAGENTP_H

#include <map>

#include "Tools/NaoTime.h"
#include "Tools/DataStructures/Printable.h"
#include "Representations/Infrastructure/FrameInfo.h"
#include "Representations/Modeling/TeamMessageData.h"

using namespace naoth;

class TeamMessageNTP : public naoth::Printable
{
public:
    /** Stores message time inforamtions. */
    struct Player
    {
        /** the playernumber */
        unsigned int number;
        /** last ntp update of this player */
        FrameInfo lastNtpUpdate;
        /** the fastegetTimeInMilliSecondsst round trip time / latency and the resulting time offset (difference) */
        long long rtt = 0.0;
        long long latency = 0.0;
        long long offset = 0.0;

        Player(unsigned int n = 0) : number(n) {}

        /**
         * @brief Returns the (estimated) timestamp of the player
         * @return timestamp of the player
         */
        long long getTimeInMilliSeconds() const {
            return naoth::NaoTime::getSystemTimeInMilliSeconds() - offset;
        }

        /**
         * @brief Determines, whether or not a ntp module is enabled and this player was updated.
         * @return true, if the player has valid ntp infos, false otherwise
         */
        bool isNtpActive() const { return lastNtpUpdate.getFrameNumber() > 0; }

        /**
         * @brief Prints some information to the stream
         * @param stream where the infos are printed to
         */
        void print(std::ostream &stream) const
        {
            stream << "player: " << number << ",\n";

            if(lastNtpUpdate.getFrameNumber() > 0) {
                stream << "  - rtt: "       << rtt << "ms,\n"
                       << "  - latency: "   << latency << "ms,\n"
                       << "  - offset: "    << offset << "ms,\n"
                       << "  - timestamp: " << getTimeInMilliSeconds() << "ms\n";
            } else {
                stream << "  - [[ no ntp data ]]\n";
            }
        }
    };

    /** Collection for storing the various player time measure infos */
    std::map<unsigned int, Player> data;

    /**
     * @brief Prints the available time measure infos to the given stream.
     * @param stream the stream, where the infos should be printed to
     */
    virtual void print(std::ostream& stream) const
    {
        stream << "TeamMessageNTP ("<<data.size()<<"):\n";
        if(data.empty()) {
            stream << "\t[NONE]\n";
        } else {
            // iterate through players and print data
            for (const auto& it : data) {
                it.second.print(stream);
            }
        }
    }

    /**
     * @brief Returns the team message statistic representation of a player with the player number "number".
     *        If there's no player with the number, a new one is created.
     * @param number the player number
     * @return Player reference to the players time measure info
     */
    Player& getPlayer(unsigned int number) {
        Player& ply = data[number];
        // new player struct
        if(ply.number == 0) {
            ply.number = number;
        }
        return ply;
    }

    /**
     * @brief Determines, whether or not a ntp module is enabled and this player was updated.
     *        This is a convenience method.
     * @param player_number the player number to check
     * @return true|false
     */
    bool isNtpActive(unsigned int player_number) const {
        const auto& player = data.find(player_number);
        return player != data.cend() && player->second.isNtpActive();
    }

    /**
     * @brief Returns the (estimated) timestamp of the player
     *        This is a convenience method.
     * @param player_number the player number to check
     * @return true|false
     */
    long long getTimeInMilliSeconds(unsigned int player_number) const {
        const auto& player = data.find(player_number);
        return player != data.cend() ? player->second.getTimeInMilliSeconds() : 0;
    }
};

#endif // TEAMMESSAGENTP_H
