#pragma once
#include <vector>

namespace hwsim {

// forward declaration of enum WireEnd
enum class WireEnd;

// forward declaration for the graph interfaces
struct SimWireEdge;
struct SimWireVertex;

// class for the simulation representation of a wire, 
// which is used for heat and wave propagation
// do not inherit!
class SimWire
{

	friend class SimNode;
	friend class SimController;

public:

	// struct containing configuration options used in wire initialization
	struct Config 
	{
		unsigned int storeTimesteps;
		unsigned int nx;
		float dx;

		Config(): storeTimesteps(0), nx(0), dx(0) {};

		Config(unsigned int _storeTimesteps, unsigned int _nx, float _dx) :
			storeTimesteps(_storeTimesteps), nx(_nx), dx(_dx)
		{};
	};

	// struct containing pointers to vectors that contain the initial state
	struct InitState 
	{
		// !!!: use nullptr to tell the initializer to use the 
		// default initial state instead

		std::vector<float>* initWave;
		std::vector<float>* initWaveVelocity;
		std::vector<float>* initHeat;

		// these will probably be taken out later and put somewhere else,
		// because they're arguably not part of the 'state'
		std::vector<float>* waveSpeed;
		std::vector<float>* damping;
		std::vector<float>* diffusivity;
	};

	SimWire();
	SimWire(const Config& config);
	~SimWire();

	// updates one timestep for both wave and heat
	void update(float dt);

	bool initialize(const Config& config, const InitState& initState, float dt);

	// initialize the wire, given initial wave and wave velocity and given initial heat
	bool initialize(const Config& config, std::vector<float>& initWave,
		std::vector<float>& initWaveVelocity,
		std::vector<float>& initHeat,
		std::vector<float>& waveSpeed,
		std::vector<float>& damping,
		std::vector<float>& diffusivity,
		float dt);

	// initialization without configuration
	bool initialize(std::vector<float>& initWave,
		std::vector<float>& initWaveVelocity,
		std::vector<float>& initHeat,
		std::vector<float>& waveSpeed,
		std::vector<float>& damping,
		std::vector<float>& diffusivity,
		float dt);

	// return references to the wave and heat data at the 'current' time
	const std::vector<float>& getWave() const;
	const std::vector<float>& getHeat() const;

	// generalized versions of the above functions:
	// return the wave or heat n timesteps ago
	const std::vector<float>& getWavePast(unsigned int n) const;
	const std::vector<float>& getHeatPast(unsigned int n) const;

	// get the wave/heat in 'the future' - used by SimNode to obtain the 
	// future calculated values before the temporal index has been updated
	const std::vector<float>& getWaveFuture() const;
	const std::vector<float>& getHeatFuture() const;

	// set/get how many timesteps we're storing
	// error if setting to values smaller than 3
	void setStoreTimesteps(unsigned int storeTimesteps);
	unsigned int getStoreTimesteps() const;

	// get/set config
	bool setConfig(const Config& config);
	const Config& getConfig() const;

	// has this wire been initialized?
	bool isInitialized() const;

	// is the config valid?
	bool isConfigValid() const;

	// the corresponding SimWireEdge graph interface
	SimWireEdge* edge;

private:

	// compute wave spatial and temporal derivatives
	void _computeWaveDerivatives(float dt);

	// compuate heat spatial and temporal derivatives
	void _computeHeatDerivatives(float dt);

	// update the boundaries, using the nodes
	void _updateWaveBoundaries(std::vector<float>&wave_next, float dt);
	void _updateHeatBoundaries(std::vector<float>&heat_next, float dt);

	// update the temporal index - done at the start/very end of each sim tick
	void _updateTemporalIndex();

	Config _config;

	// the wave speed over the wire
	std::vector<float> _waveSpeed;

	// the damping over the wire
	std::vector<float> _damping;

	// the "thermal" diffusivity of the wire
	std::vector<float> _diffusivity;

	// contains the wave amplitude data, for the past n (probably 3) timesteps
	std::vector<std::vector<float>> _wave;

	// contains the heat data, for the past n (probably 3 (?)) timesteps
	std::vector<std::vector<float>> _heat;

	// storage for derivatives of various orders
	std::vector<std::vector<float>> _wave_x;
	std::vector<std::vector<float>> _wave_xx;
	std::vector<std::vector<float>> _wave_t;

	std::vector<std::vector<float>> _heat_x;
	std::vector<std::vector<float>> _heat_xx;
	
	// store the 'damping energy differential' - energy lost due to damping
	
	// what's the index of the 'current' timestep?
	unsigned int _currentTimestepIndex;

	// has this wire been initialized?
	bool _isInitialized;

	// is the current wire configuration valid?
	bool _isConfigValid;
};

};