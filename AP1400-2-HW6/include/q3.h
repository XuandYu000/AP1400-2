#ifndef Q3_H
#define Q3_H

#include<queue>

namespace q3
{
    struct Flight
    {
        std::string flight_number;
        size_t duration;
        size_t connections;
        size_t connection_times;
        size_t price;
    };

    inline auto gather_flights(std::string fileName)
    {
        fileName = "../resources/" + fileName;
        std::ifstream file(fileName);
        if (!file.is_open())
        {
            throw std::runtime_error("Fail to open file with filename " + fileName);
        }

        auto func = [](Flight& a, Flight& b)
        {
            auto sum = [](Flight& flight)
            {
                return flight.duration + flight.connection_times + 3 * flight.price;
            };
            return sum(a) > sum(b);
        };

        std::vector<Flight> flights;
        std::string line;
        auto clear = [](std::string& token)
        {
            // std::remove将要remove值移到字符串最后，然后erase(…, end)删除remove中指定的字符（不管数量有多少）
            token.erase(std::remove(token.begin(), token.end(), ' '), token.end());
        };
        while (std::getline(file, line))
        {
            Flight flight;
            char delim = '-';
            std::istringstream ss(line);
            std::string token;
            std::getline(ss, token, delim);
            auto pre_process = [&ss, &token, &delim, &clear](std::string filter)
            {
                // 每次将std::istringstream给输出到token中会将指针移动到下个delim的位置
                std::getline(ss, token, delim);
                clear(token);
                token.erase(0, filter.size());
            };
            // parse flight_number
            pre_process("filter_number:");
            flight.flight_number = token;

            // parse duration
            pre_process("duration:");

            auto parse_time = [](std::string& token) -> size_t
            {
                size_t hours = 0, minutes = 0;
                size_t hour_pos = token.find('h');
                if (hour_pos != std::string::npos)
                {
                    hours = std::stoul(token.substr(0, hour_pos));
                    token.erase(0, hour_pos + 1);
                }
                size_t minute_pos = token.find('m');
                if (minute_pos != std::string::npos)
                {
                    minutes = std::stoul(token.substr(0, minute_pos));
                }
                return hours * 60 + minutes;
            };
            flight.duration = parse_time(token);

            // parse connections
            pre_process("connections:");
            flight.connections = std::stoul(token);

            // parse connectino_times
            pre_process("connection_times:");
            auto process_connection_times = [&parse_time](std::string& token) -> size_t
            {
                size_t result = 0;
                std::istringstream ss(token);
                char delim = ',';
                std::string time;
                while (std::getline(ss, time, delim))
                {
                    result += parse_time(time);
                }
                return result;
            };
            flight.connection_times = process_connection_times(token);

            // parse price
            pre_process("price:");
            flight.price = std::stoul(token);

            // add flight to flights
            flights.push_back(flight);
        }

        std::priority_queue<Flight, std::vector<Flight>, decltype(func)> pq(func, flights);
        return pq;
    }
}

#endif //Q3_H